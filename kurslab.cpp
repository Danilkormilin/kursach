#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"graphics.h"

enum objtype {KVAD,ROMB,PARL,SKVAD};
enum savetype {TXT,BMP};

savetype s;

typedef struct obj
{
   char text[101];
   int x,y,sizex,sizey;
   objtype t;
} obj;

typedef struct arrow
{
   char text[101];
   int  x1,x2,y1,y2;
} arrow;

int inputtextmode,temptexti;
char temptext[101],temptextbuff[101],Sizex[101],Sizey[101],
     savebmp[104] = "Save.bmp\0",
                    savetxt[104] = "Save.txt\0",
                                   opentxt[104] = "Open.txt\0";
int END = 0;
int actoa = 0;
int p = 0,
    nomobj, nomarr, kolobj, kolarr,
    typeoa = 0, typearrow;

obj objm[100];
arrow arrm[100];

IMAGE *MAIN;

void skvad(int x, int y, int sizex, int sizey, int tcol) //скругленный квадрат
{
   if (tcol == 1)
      setcolor(RED);
   else
      setcolor(BLACK);
   line(x+ 10,y,x+sizex - 10,y);
   line(x+ 10,y + sizey,x+sizex - 10,y + sizey);
   line(x,y+ 10,x,y + sizey - 10);
   line(x+ sizex,y+10,x+sizex,y+sizey -10);
   arc(x + 10, y + 10, 90, 180, 10);
   arc(x + 10, y + sizey - 10, 180, 270, 10);
   arc(x + sizex - 10, y + sizey - 10, 270, 360, 10);
   arc(x + sizex - 10, y + 10, 0, 90, 10);
}

int testskvad(int x, int y, int sx, int sy) // проверка нажатия на скругленный квадрат
{
   if (((mousex()>=x && mousex()<=x+sx && mousey() >= y+10 && mousey() <= y + sy - 10) ||
         (mousex()>=x + 10 && mousex()<=x+sx - 10 && mousey() >= y && mousey() <= y + sy) ||
         (pow(mousex() - (x + 10),2) + pow(mousey() - (y + 10),2) <= 100) ||
         (pow(mousex() - (x + 10),2) + pow(mousey() - (y + sx - 10),2) <= 100) ||
         (pow(mousex() - (x + sx - 10),2) +pow(mousey() - (y + 10),2) <= 100) ||
         (pow(mousex() - (x + sx - 10),2) + pow(mousey() - (y + sx - 10),2) <= 100)) && (mousebuttons() == 1))
   {
      return (1);
   }
   else return (0);
}

void kvad(int x, int y, int sizex, int sizey, int tcol) // квадрат
{
   if (tcol == 1)
      setcolor(RED);
   else
      setcolor(BLACK);
   line(x,y,x+sizex,y);
   line(x,y,x,y + sizey);
   line(x+sizex,y,x + sizex,y + sizey);
   line(x,y + sizey,x+sizex,y + sizey);
}

int testkvad(int x, int y, int sx, int sy) // проверка нажатия на квадрат
{
   if ((mousex()>=x && mousex()<=x+sx && mousey() >= y && mousey() <= y + sy) && (mousebuttons() == 1))
   {
      return (1);
   }
   else return (0);
}

void romb(int x, int y, int sizex, int sizey, int tcol) // ромб
{
   if (tcol == 1)
      setcolor(RED);
   else
      setcolor(BLACK);
   line(x + sizex/2,y,x+sizex,y + sizey/2);
   line(x + sizex/2,y,x,y + sizey/2);
   line(x + sizex/2,y + sizey,x+sizex,y + sizey/2);
   line(x + sizex/2,y + sizey,x,y + sizey/2);
}

void tes(int x, int y, int sx, int sy) // проверка ромба (в финале убрать)
{
   int m= 0, o = 1000;
   setcolor(BLUE);
   line(0,(double)y+(double)sy/2 - ((double)m*(double)sy)/(double)sx + ((double)x*(double)sy)/(double)sx,1000,(double)y+(double)sy/2 - ((double)o*(double)sy)/(double)sx + ((double)x*(double)sy)/(double)sx);
   setcolor(GREEN);
   line(0,(double)y+(double)sy/2 - ((double)m*(double)sy)/(double)sx + ((double)x*(double)sy)/(double)sx +(double)sy,1000,(double)y+(double)sy/2 - ((double)o*(double)sy)/(double)sx + ((double)x*(double)sy)/(double)sx +(double)sy);
   setcolor(BLUE);
   line(0,(double)y-(double)sy/2 + ((double)m*(double)sy)/(double)sx - ((double)x*(double)sy)/(double)sx,1000,(double)y-(double)sy/2 + ((double)o*(double)sy)/(double)sx - ((double)x*(double)sy)/(double)sx);
   setcolor(GREEN);
   line(0,(double)y-(double)sy/2 + ((double)m*(double)sy)/(double)sx - ((double)x*(double)sy)/(double)sx+ (double)sy,1000,(double)y-(double)sy/2 + ((double)o*(double)sy)/(double)sx - ((double)x*(double)sy)/(double)sx + (double)sy);
   return;
}

int testromb(int x, int y, int sx, int sy) // проверка нажатия на ромб
{
   if ((mousey() >= (double)y+(double)sy/2 - ((double)mousex()*(double)sy)/(double)sx + ((double)x*(double)sy)/(double)sx) &&
         (mousey() <= (double)y+(double)sy/2 - ((double)mousex()*(double)sy)/(double)sx + ((double)x*(double)sy)/(double)sx +(double)sy) &&
         (mousey() >= (double)y-(double)sy/2 + ((double)mousex()*(double)sy)/(double)sx - ((double)x*(double)sy)/(double)sx) &&
         (mousey() <= (double)y-(double)sy/2 + ((double)mousex()*(double)sy)/(double)sx - ((double)x*(double)sy)/(double)sx + (double)sy) && (mousebuttons() == 1))
   {
      return (1);
   }
   else return (0);
}

void parl(int x, int y, int sizex, int sizey, int tcol) //паралелограм
{
   if (tcol == 1)
      setcolor(RED);
   else
      setcolor(BLACK);
   line(x + 10,y,x+sizex,y);
   line(x + 10,y,x,y + sizey);
   line(x+sizex,y,x + sizex - 10,y + sizey);
   line(x,y + sizey,x+sizex - 10,y + sizey);
}

int testparl(int x, int y, int sx, int sy) // проверка нажатия на паралелограмм
{
   if ((mousey() >= y) &&
         (mousey() <= y + sy) &&
         (mousey() >= (double)y - ((double)mousex()*(double)sy)/(double)10 + ((double)x*(double)sy)/(double)10 + (double)sy) &&
         (mousey() <= (double)y - ((double)mousex()*(double)sy)/(double)10 + ((double)x*(double)sy)/(double)10 + (double)sy*(double)sx/(double)10) && (mousebuttons() == 1))
   {
      return (1);
   }
   else return (0);
}

void arr(int x1,int y1, int x2, int y2,int tcol) // стрелка
{
   double fi;
   if (tcol == 1)
      setcolor(RED);
   else
      setcolor(BLACK);
   line(x1,y1,x2,y2);
   int a[6] = {x2,y2},b[6] = {x2,y2},dy =y2 - y1,dx = x2 -x1;
   if (x1 == x2)
   {
      if (dy > 0)
      {
         a[2] = b[2] = x2;
         a[3] = b[3] = y2 - 5;
         fi = (acos(-1)*3)/2;
      }
      else
      {
         a[2] = b[2] = x2;
         a[3] = b[3] = y2 + 5;
         fi = acos(-1)/2;
      }
   }
   else if (y1 == y2)
   {
      if (dx > 0)
      {
         a[2] = b[2] = x2 - 5;
         a[3] = b[3] = y2;
         fi = acos(-1);
      }
      else
      {
         a[2] = b[2] = x2 + 5;
         a[3] = b[3] = y2;
         fi = 0;
      }
   }
   else if (dx > 0)
   {
      fi =acos(-1) + atan((double)dy/(double)dx);
      a[2] = b[2] = x2 + int(cos(fi)* 5);
      a[3] = b[3] = y2+ int(sin(fi)* 5);
   }
   else
   {
      fi =atan((double)dy/(double)dx);
      a[2] = b[2] = x2 + int(cos(fi)* 5);
      a[3] = b[3] = y2+ int(sin(fi)* 5);
   }
   a[4] = x2 + int(cos(fi + acos(-1)/6)* 10);
   b[4] = x2 + int(cos(fi- acos(-1)/6)* 10);
   a[5] = y2 + int(sin(fi + acos(-1)/6)* 10);
   b[5] = y2 + int(sin(fi- acos(-1)/6)* 10);
   if (tcol == 1)
      setfillstyle(SOLID_FILL,RED);
   else
      setfillstyle(SOLID_FILL,BLACK);
   fillpoly(3, a);
   fillpoly(3, b);
}

void drawarrow(arrow arro, int tcol) // рисовани стрелки с текстом, кругами
{
   arr(arro.x1,arro.y1,arro.x2,arro.y2,tcol);
   int dx = arro.x2 - arro.x1, dy = arro.y2 - arro.y1;
   setbkmode(TRANSPARENT);
   setcolor(BLACK);
   settextjustify(LEFT_TEXT,TOP_TEXT);
   if (dx == 0)
   {
      outtextxy((arro.x1 + arro.x2)/2 + 5,(arro.y1 + arro.y2)/2 + 5,arro.text);
   }
   else if ((double)dy/(double)dx < 0)
   {
      outtextxy((arro.x1 + arro.x2)/2 + 5,(arro.y1 + arro.y2)/2 + 5,arro.text);
   }
   else
   {
      outtextxy((arro.x1 + arro.x2)/2 + 5,(arro.y1 + arro.y2)/2 - 15,arro.text);
   }
   if (tcol)
   {
      if (typearrow == 1)
      {
         setfillstyle(SOLID_FILL,RED);
         fillellipse(arro.x1, arro.y1, 5,5);
         setfillstyle(SOLID_FILL,BLUE);
         fillellipse((arro.x1 + arro.x2)/2, (arro.y1 + arro.y2)/2, 5,5);
         setfillstyle(SOLID_FILL,BLUE);
         fillellipse(arro.x2, arro.y2, 5,5);
      }
      else if (typearrow == 2)
      {
         setfillstyle(SOLID_FILL,BLUE);
         fillellipse(arro.x1, arro.y1, 5,5);
         setfillstyle(SOLID_FILL,RED);
         fillellipse((arro.x1 + arro.x2)/2, (arro.y1 + arro.y2)/2, 5,5);
         setfillstyle(SOLID_FILL,BLUE);
         fillellipse(arro.x2, arro.y2, 5,5);
      }
      else
      {
         setfillstyle(SOLID_FILL,BLUE);
         fillellipse(arro.x1, arro.y1, 5,5);
         setfillstyle(SOLID_FILL,BLUE);
         fillellipse((arro.x1 + arro.x2)/2, (arro.y1 + arro.y2)/2, 5,5);
         setfillstyle(SOLID_FILL,RED);
         fillellipse(arro.x2, arro.y2, 5,5);
      }
   }
}

int testline(int x1, int x2, int y1, int y2)   // проверка нажатия на линию стрелки
{
   if (x1 == x2)
   {
      if (mousex() == x1 && mousey() <= fmax((double)y1, (double)y2) && mousey() >= fmin((double)y1, (double)y2)) return (1);
      else return (0);
   }
   else if (y1 == y2)
   {
      if (mousey() == y1 && mousex() <= fmax((double)x1, (double)x2) && mousex() >= fmin((double)x1, (double)x2)) return (1);
      else return (0);
   }
   else
   {
      if (mousex() <= fmax((double)x1, (double)x2) && mousex() >= fmin((double)x1, (double)x2) &&
            (double)mousey() <= (((double)mousex() - (double)x1)*((double)y2 - (double)y1))/((double)x2 - (double)x1) + (double)y1 + 1 &&
            (double)mousey() >= (((double)mousex() - (double)x1)*((double)y2 - (double)y1))/((double)x2 - (double)x1) + (double)y1 - 1) return (1);
      else return (0);
   }
   return (0);
}

int testarr(int x1, int x2, int y1, int y2)     //проверка нажатия на стрелку
{
   if (pow(mousex() - x1,2) + pow(mousey() - y1,2) <= 25 && mousebuttons() == 1) return (1);
   else if (pow(mousex() - x2,2) + pow(mousey() - y2,2) <= 25 && mousebuttons() == 1) return (3);
   else if ((pow(mousex() - (x2 + x1)/2,2) + pow(mousey() - (y2 + y1)/2,2) <= 25  || testline(x1,x2,y1,y2)) && mousebuttons() == 1) return (2);
   return (0);
}

void inputtext(char *a, int typ) //ввод текста
{
   if (inputtextmode == 0)
   {
      for (int i = 0; i < 101; i++)
      {
         temptext[i] = a[i];
         temptexti = i;
         if(a[i] == '\0') break;
      }
      inputtextmode = typ;
   }
   int b;
   if (kbhit())
   {
      b = getch();
      if (b == 0)
      {
         b = getch();
         if (b == KEY_SHIFT)
         {
            if (kbhit())
            {
               b = getch();/**************************************************************************************/
               if (b == 0)
               {
                  b = getch();
               }
               else
               {
                  if (b == KEY_BACKSPACE)
                  {
                     if (temptexti>0)
                     {
                        //printf("3");
                        temptexti--;
                        temptext[temptexti] = '\0';
                        return;
                     }
                  }
                  else
                  {
                     if (temptexti<100)
                     {
                        temptext[temptexti] = (char)b;
                        temptexti++;
                        temptext[temptexti] = '\0';
                        return;
                     }
                  }
               }
               /****************************************************************************************************/
            }
         }
      }
      else
      {
         if (b == KEY_BACKSPACE)
         {
            if (temptexti>0)
            {
               temptexti--;
               temptext[temptexti] = '\0';
               return;
            }
         }
         else
         {
            if (temptexti<100)
            {
               temptext[temptexti] = (char)b;
               temptexti++;
               temptext[temptexti] = '\0';
               return;
            }
         }
      }
   }
   if (mousex() >=730 && mousey() >= 2 && mousex() <= 788 && mousey() <= 56 && mousebuttons() == 1)
   {
      for (int i= 0; i<=temptexti; i++)
      {
         a[i] = temptext[i];
      }
      inputtextmode = 0;
      if (typ == 1)
      {
         ;
      }
      else if (typ == 2)
      {
         if (s == BMP)
         {
            if (temptexti<4 || a[temptexti - 1] != 'p' || a[temptexti - 2] != 'm' || a[temptexti - 1] != 'b' || a[temptexti - 1] != '.')
            {
               a[temptexti] = '.';
               a[temptexti+1] = 'b';
               a[temptexti+2] = 'm';
               a[temptexti+3] = 'p';
               a[temptexti+4] = '\0';
            }
         }
         else
         {
            if (temptexti<4 || a[temptexti - 1] != 't' || a[temptexti - 2] != 'x' || a[temptexti - 1] != 't' || a[temptexti - 1] != '.')
            {
               a[temptexti] = '.';
               a[temptexti+1] = 't';
               a[temptexti+2] = 'x';
               a[temptexti+3] = 't';
               a[temptexti+4] = '\0';
            }
         }
      }
      else if (typ == 3)
      {
         if (temptexti<4 || a[temptexti - 1] != 't' || a[temptexti - 2] != 'x' || a[temptexti - 1] != 't' || a[temptexti - 1] != '.')
         {
            a[temptexti] = '.';
            a[temptexti+1] = 't';
            a[temptexti+2] = 'x';
            a[temptexti+3] = 't';
            a[temptexti+4] = '\0';
         }
      }
   }
   //printf("2");
   return;
   /***********************************************************************************************************************************************************************************************/
}

void testallarrows()    //проверка нажатия на все стрелки
{
   for (int i = 0; i < kolarr; i++)
   {
      switch (testarr(arrm[i].x1,arrm[i].x2,arrm[i].y1,arrm[i].y2))
      {
      case (1):
         actoa = 1;
         typeoa = 2;
         nomarr = i;
         typearrow = 1;
         return;
      case (2):
         actoa = 1;
         typeoa = 2;
         nomarr = i;
         typearrow = 2;
         return;
      case (3):
         actoa = 1;
         typeoa = 2;
         nomarr = i;
         typearrow = 3;
         return;
      case (0):
         break;
      }
   }
}

void drawobj(obj ob,int tcol)   //рисование объекта
{
   switch (ob.t)
   {
   case (KVAD):
      kvad(ob.x,ob.y,ob.sizex,ob.sizey,tcol);
      break;
   case (SKVAD):
      skvad(ob.x,ob.y,ob.sizex,ob.sizey,tcol);
      break;
   case (ROMB):
      romb(ob.x,ob.y,ob.sizex,ob.sizey,tcol);
      //tes(ob.x,ob.y,ob.sizex,ob.sizey);
      break;
   case (PARL):
      parl(ob.x,ob.y,ob.sizex,ob.sizey,tcol);
      break;
   }
   char a[102];
   snprintf(a,(ob.sizex - 20)/8,"%s",ob.text);
   a[(ob.sizex - 20)/8] = '\0';
   setbkmode(TRANSPARENT);
   setcolor(BLACK);
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   outtextxy(ob.x + ob.sizex/2, ob.y + ob.sizey/2 + 5,a);
}

void drawallobjects()   //рисование всех оюъектов
{
   for (int i = 0; i < kolobj; i++)
   {
      if (i == nomobj  && actoa == 1 && typeoa == 1)
         drawobj(objm[i],1);
      else
         drawobj(objm[i],0);
   }
}

void drawallarrows()    //рисование всех стрелок
{
   for (int i = 0; i < kolarr; i++)
   {
      if (i == nomarr && actoa == 1 && typeoa == 2)
         drawarrow(arrm[i],1);
      else
         drawarrow(arrm[i],0);
   }
}

void addobject(objtype t)      // добавление объекта
{
   if (kolobj < 100)
   {
      actoa = 1;
      typeoa = 1;
      kolobj++;
      nomobj = kolobj-1;
      objm[nomobj].t = t;
      objm[nomobj].x = getmaxx()/2;
      objm[nomobj].y = getmaxy()/2;
      objm[nomobj].sizex = 100;
      objm[nomobj].sizey = 100;
      char a[101] = "Текст\0";
      for (int i = 0 ; i < 101; i++)
      {
         objm[nomobj].text[i] = a[i];
         if (a[i] == '\0') break;
      }
   }
}

void addarrow() //добавление стрелки
{
   if (kolarr < 100)
   {

      actoa = 1;
      typeoa = 2;
      kolarr++;
      nomarr = kolarr-1;
      typearrow = 2;
      arrm[nomarr].x1 = getmaxx()/2;
      arrm[nomarr].y1 = getmaxy()/2;
      arrm[nomarr].x2 = getmaxx()/2+100;
      arrm[nomarr].y2 = getmaxy()/2+100;
      char a[101] = "Текст\0";
      for (int i = 0 ; i < 101; i++)
      {
         arrm[nomarr].text[i] = a[i];
         if (a[i] == '\0') break;
      }
   }
}

void dellarrow() //удаление стрелки
{
   for(int i = nomarr; i <kolarr - 1; i++)
   {
      arrm[i] = arrm[i+1];
   }
   kolarr--;
   actoa = 0;
   typeoa = 0;
}

void dellobj() //удаление объекта
{
   for(int i = nomobj; i <kolobj - 1; i++)
   {
      objm[i] = objm[i+1];
   }
   kolobj--;
   actoa = 0;
   typeoa = 0;
}

int buttonobj(int left,int top, int right,int bottom,void (*f)(objtype), objtype t)     //кнопка для добавления объектов (вызова функции с параметром objtype)
{
   if (mousex() >= left && mousex() <= right && mousey() >= top && mousey() <= bottom && mousebuttons() == 1)
   {
      //printf("1");
      f(t);
      delay(100);
      return (1);
   }
   else return (0);
}

int button(int left,int top, int right,int bottom,void (*f)())  //кнопка (вызов функции ()(void))
{
   if (mousex() >= left && mousex() <= right && mousey() >= top && mousey() <= bottom && mousebuttons() == 1)
   {
      f();
      delay(100);
      return (1);
   }
   else return (0);
}

void testallobjects()   //проверка нажатия на все объекты
{
   int j;
   for (int i = 0; i < kolobj; i++)
   {
      switch (objm[i].t)
      {
      case (KVAD):
         j = testkvad(objm[i].x,objm[i].y,objm[i].sizex,objm[i].sizey);
         break;
      case (SKVAD):
         j = testskvad(objm[i].x,objm[i].y,objm[i].sizex,objm[i].sizey);
         break;
      case (ROMB):
         j = testromb(objm[i].x,objm[i].y,objm[i].sizex,objm[i].sizey);
         break;
      case (PARL):
         j = testparl(objm[i].x,objm[i].y,objm[i].sizex,objm[i].sizey);
         break;
      }
      if (j)
      {
         actoa = 1;
         typeoa = 1;
         nomobj = i;
         return;
      }
   }
   return;
}

int inpactobj() //работа с активным объектом
{
   int a;
   if (kbhit())
   {
      a = getch();
      if (a == 0)
      {
         a = getch();
         switch (a)
         {
            case (KEY_DELETE):
            dellobj();
            return (1);
         case (KEY_LEFT):
            if (objm[nomobj].x > 153)objm[nomobj].x--;
            return (1);
         case (KEY_RIGHT):
            if (objm[nomobj].x < 788)objm[nomobj].x++;
            return (1);
         case (KEY_UP):
            if (objm[nomobj].y > 59)objm[nomobj].y--;
            return (1);
         case (KEY_DOWN):
            if (objm[nomobj].y < 588)objm[nomobj].y++;
            return (1);
         }
      }
   }
   if (mousex() >= 15 && mousey() >= 320 && mousex() <= 61 && mousey() <= 341 && mousebuttons() == 1)
   {
      if (objm[nomobj].sizex > 50) objm[nomobj].sizex--;
      return (1);
   }
   if (mousex() >= 94 && mousey() >= 320 && mousex() <= 140 && mousey() <= 341 && mousebuttons() == 1)
   {
      if (objm[nomobj].sizex < 500 && objm[nomobj].sizex + objm[nomobj].x <= 788) objm[nomobj].sizex++;
      return (1);
   }
   if (mousex() >= 15 && mousey() >= 374 && mousex() <= 61 && mousey() <= 395 && mousebuttons() == 1)
   {
      if (objm[nomobj].sizey > 50) objm[nomobj].sizey--;
      return (1);
   }
   if (mousex() >= 94 && mousey() >= 374 && mousex() <= 140 && mousey() <= 395 && mousebuttons() == 1)
   {
      if (objm[nomobj].sizey < 500 && objm[nomobj].sizey + objm[nomobj].y <= 588) objm[nomobj].sizey++;
      return (1);
   }
   if (mousex() >= 153 && mousey() >= 59 && mousex() <= 788 && mousey() <= 588 && mousebuttons() == 2)
   {
      objm[nomobj].x = mousex() - objm[nomobj].sizex/2;
      objm[nomobj].y = mousey() - objm[nomobj].sizey/2;
      if (objm[nomobj].x < 153) objm[nomobj].x = 153;
      if (objm[nomobj].y < 59) objm[nomobj].y = 59;
      if (objm[nomobj].x + objm[nomobj].sizex > 788) objm[nomobj].x = 788 - objm[nomobj].sizex;
      if (objm[nomobj].y + objm[nomobj].sizey > 588) objm[nomobj].y = 588 - objm[nomobj].sizey;
      return (1);
   }
   if (mousex() >= 298 && mousey() >= 2 && mousex() <= 726 && mousey() <= 56 && mousebuttons() == 1)
   {
      inputtext(objm[nomobj].text, 1);
      return (1);
   }
   return (0);
}

void testobjtoarr(int *x, int *y)       //проверка краев объектов для движения стрело (магнитность)
{
   int leftx, lefty, rightx, righty,botx, boty,topx, topy;
   for (int i = 0; i < kolobj; i++)
   {
      botx = objm[i].x + objm[i].sizex/2;
      topx = objm[i].x + objm[i].sizex/2;
      boty = objm[i].y + objm[i].sizey;
      topy = objm[i].y;
      if (objm[i].t == PARL)
      {
         leftx = objm[i].x+ 5;
         rightx = objm[i].x + objm[i].sizex - 5;
         lefty= (double)objm[i].y - ((double)(leftx)*(double)objm[i].sizey)/(double)10 + ((double)objm[i].x*(double)objm[i].sizey)/(double)10 + (double)objm[i].sizey;
         righty = (double)objm[i].y - ((double)(rightx)*(double)objm[i].sizey)/(double)10 + ((double)objm[i].x*(double)objm[i].sizey)/(double)10 + (double)objm[i].sizey*(double)objm[i].sizex/(double)10;
      }
      else
      {
         leftx = objm[i].x;
         rightx = objm[i].x + objm[i].sizex;
         lefty = objm[i].y + objm[i].sizey/2;
         righty = objm[i].y + objm[i].sizey/2;
      }
      if (pow(mousex() - botx,2) + pow(mousey() - boty,2) <= 25)
      {
         *x = botx;
         *y = boty;
         return;
      }
      else if (pow(mousex() - topx,2) + pow(mousey() - topy,2) <= 25)
      {
         *x = topx;
         *y = topy;
         return;
      }
      else if (pow(mousex() - leftx,2) + pow(mousey() - lefty,2) <= 25)
      {
         *x = leftx;
         *y = lefty;
         return;
      }
      else if (pow(mousex() - rightx,2) + pow(mousey() - righty,2) <= 25)
      {
         *x = rightx;
         *y = righty;
         return;
      }
   }
   return;
}

void testarrtoarr(int *x, int *y)       //проверка концов стрелок для движения стрелок
{
   int stx,sty,fx,fy;
   for (int i = 0; i < kolarr; i++)
   {
      if (i != nomarr)
      {
         stx = arrm[i].x1;
         sty = arrm[i].y1;
         fx = arrm[i].x2;
         fy = arrm[i].y2;
         if (pow(mousex() - stx,2) + pow(mousey() - sty,2) <= 25)
         {
            *x = stx;
            *y = sty;
            return;
         }
         else if (pow(mousex() - fx,2) + pow(mousey() - fy,2) <= 25)
         {
            *x = fx;
            *y = fy;
            return;
         }
      }
   }
   return;
}

int movearr(int *x, int *y)     //движение конца стрелки
{
   int a;
   if (kbhit())
   {
      a = getch();
      if (a == 0)
      {
         a = getch();
         switch (a)
         {
            case (KEY_DELETE):
            dellarrow();
            return (1);
         case (KEY_LEFT):
            if ((*x) > 153)(*x)--;
            return (1);
         case (KEY_RIGHT):
            if ((*x) < 788)(*x)++;
            return (1);
         case (KEY_UP):
            if ((*y) > 59)(*y)--;
            return (1);
         case (KEY_DOWN):
            if ((*y) < 588)(*y)++;
            return (1);
         }
      }
   }
   if (mousex() >= 153 && mousey() >= 59 && mousex() <= 788 && mousey() <= 588 && mousebuttons() == 2)
   {
      *x = mousex();
      *y = mousey();
      testarrtoarr(x,y);
      testobjtoarr(x,y);
      return (1);
   }
   return (0);
}

int movefullarr(int *x1, int *x2, int *y1, int *y2)       //движение всей стрелки
{
   int X1 = *x1,X2 = *x2,Y1 = *y1,Y2 = *y2;
   int c1x,cx,c1y,cy,dx1,dx2,dy1,dy2,
       maxx = (int)fmax((double)X1,(double)X2),
       minx = (int)fmin((double)X1,(double)X2),
       maxy = (int)fmax((double)Y1,(double)Y2),
       miny = (int)fmin((double)Y1,(double)Y2);
   c1x = cx = (X1+X2)/2;
   c1y = cy = (Y1+Y2)/2;
   dx1 = X1 - cx;
   dx2 = X2 - cx;
   dy1 = Y1 - cy;
   dy2 = Y2 - cy;
   int a;
   if (kbhit())
   {
      a = getch();
      if (a == 0)
      {
         a = getch();
         switch (a)
         {
            case (KEY_DELETE):
            dellarrow();
            return (1);
         case (KEY_LEFT):
            if ((minx) > 153) cx--;
            break;
         case (KEY_RIGHT):
            if ((maxx) < 788) cx++;
            break;
         case (KEY_UP):
            if ((miny) > 59) cy--;
            break;
         case (KEY_DOWN):
            if ((maxy) < 588) cy++;
            break;
         }
      }
   }
   if (mousex() >= 153 && mousey() >= 59 && mousex() <= 788 && mousey() <= 588 && mousebuttons() == 2)
   {
      cx = mousex();
      cy = mousey();
      if (cx - (c1x - minx) < 153) cx = 153 + (c1x - minx);
      if (cy - (c1y - miny) < 59) cy = 59 + (c1y - miny);
      if (cx + (maxx - c1x) > 788) cx = 788 - (maxx - c1x);
      if (cy + (maxy - c1y) > 588) cy = 588 - (maxy - c1y);
   }
   (*x1) = cx + dx1;
   (*x2) = cx + dx2;
   (*y1) = cy + dy1;
   (*y2) = cy + dy2;
   if (cx != c1x || cy != c1y) return (1);
   else return (0);
}

int inpactarrow()       //работа с активной стрелкой
{
   if (typearrow == 1)
   {
      if (movearr(&arrm[nomarr].x1,&arrm[nomarr].y1)) return (1);
   }
   else if (typearrow == 2)
   {
      if (movefullarr(&arrm[nomarr].x1,&arrm[nomarr].x2,&arrm[nomarr].y1,&arrm[nomarr].y2)) return (1);
   }
   else if (typearrow == 3)
   {
      if (movearr(&arrm[nomarr].x2,&arrm[nomarr].y2)) return (1);
   }
   if (mousex() >= 298 && mousey() >= 2 && mousex() <= 726 && mousey() <= 56 && mousebuttons() == 1)
   {
      inputtext(arrm[nomarr].text, 1);
      return (1);
   }
   return (0);
}

void Setup()    //установка стартовых параметров
{
   actoa =0;
   typeoa = 0;
   nomobj = 0;
   nomarr = 0;
   kolobj = 0;
   kolarr = 0;
   typearrow = 0;
   inputtextmode = 0;
   s = BMP;
   MAIN = loadBMP("MAIN.jpg");
}

void Input() // ввод
{
   if (inputtextmode != 0)
   {
      //printf("1");
      if (inputtextmode == 1)
      {
         if (typeoa == 1)
         {
            inputtext(objm[nomobj].text,inputtextmode);
         }
         else
         {
            inputtext(arrm[nomarr].text,inputtextmode);
         }
      }
      else if (inputtextmode == 2)
      {
         if (s == BMP)
         {
            inputtext(savebmp,inputtextmode);
         }
         else
         {
            inputtext(savetxt,inputtextmode);
         }
      }
      else
      {
         inputtext(opentxt,inputtextmode);
      }
      return;
   }
   if (actoa == 1)
   {
      if (typeoa == 1)
      {
         if (inpactobj() == 1) return;
      }
      else if (typeoa == 2)
      {
         if (inpactarrow() == 1) return;
      }
   }
   testallobjects();
   testallarrows();
   while (kbhit()) getch();
   if (buttonobj(1,77,150,113,addobject,KVAD) == 1) return;
   if (buttonobj(1,115,150,153,addobject,PARL)) return;
   if (buttonobj(1,155,150,193,addobject,ROMB)) return;
   if (buttonobj(1,195,150,234,addobject,SKVAD)) return;
   if (button(1,236,150,273,addarrow)) return;
}

void Draw()     //рисование
{
   p = 1 - p;
   setactivepage(p);
   clearviewport();
   putimage(0, 0, MAIN, COPY_PUT);
   drawallobjects();
   drawallarrows();
   if (actoa == 1 && typeoa == 1)
   {
      setbkmode(TRANSPARENT);
      setcolor(BLACK);
      settextjustify(LEFT_TEXT, TOP_TEXT);
      outtextxy(78,303,itoa(objm[nomobj].sizex,Sizex,10));
      outtextxy(78,357,itoa(objm[nomobj].sizey,Sizey,10));
   }
   if (inputtextmode != 0)
   {
      setbkmode(TRANSPARENT);
      setcolor(BLACK);
      settextjustify(LEFT_TEXT, TOP_TEXT);
      outtextxy(305,27,temptext);
   }
   setvisualpage(p);
}

int main()      //программа
{
   initwindow(788,588);
   Setup();
   while (!END)
   {
      Draw();
      Input();
   }
   closegraph();
}
