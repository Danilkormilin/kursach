#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"graphics.h"

enum objtype {KVAD,ROMB,PARL,SKVAD};
enum savetype {TXT,BMP};

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
char temptext[101],temptextbuff[101];
int END = 0;
int actoa = 0;
int p = 0,
    nomobj, nomarr, kolobj, kolarr,
    typeoa = 0, typearrow;

obj objm[100];
arrow arrm[100];

IMAGE* MAIN;

void skvad(int x, int y, int sizex, int sizey, int tcol) //скругленный квадрат
{
   if(tcol == 1)
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

int testskvad(int x, int y, int sx, int sy)
{
   if(((mousex()>=x && mousex()<=x+sx && mousey() >= y+10 && mousey() <= y + sy - 10) || 
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

void kvad(int x, int y, int sizex, int sizey, int tcol)
{
    if(tcol == 1)
      setcolor(RED);
   else
      setcolor(BLACK);
   line(x,y,x+sizex,y);
   line(x,y,x,y + sizey);
   line(x+sizex,y,x + sizex,y + sizey);
   line(x,y + sizey,x+sizex,y + sizey);
}

int testkvad(int x, int y, int sx, int sy)
{
   if ((mousex()>=x && mousex()<=x+sx && mousey() >= y && mousey() <= y + sy) && (mousebuttons() == 1))
      {
      return (1);
   }
   else return (0);
}

void romb(int x, int y, int sizex, int sizey, int tcol)
{
   if(tcol == 1)
      setcolor(RED);
   else
      setcolor(BLACK);
   line(x + sizex/2,y,x+sizex,y + sizey/2);
   line(x + sizex/2,y,x,y + sizey/2);
   line(x + sizex/2,y + sizey,x+sizex,y + sizey/2);
   line(x + sizex/2,y + sizey,x,y + sizey/2);
}

void tes(int x, int y, int sx, int sy)
{int m= 0, o = 1000;
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

int testromb(int x, int y, int sx, int sy)
{
   //setcolor(BLUE);
  // line(0,(double)y+(double)sy/2 - ((double)x*(double)sy)/(double)sx,1000,(double)y+(double)sy/2 - (1000*(double)sy)/(double)sx + ((double)x*(double)sy)/(double)sx);
 //  line(0,(double)y+(double)sy/2 - ((double)x*(double)sy)/(double)sx +(double)sy,1000,(double)y+(double)sy/2 - (1000*(double)sy)/(double)sx + ((double)x*(double)sy)/(double)sx +(double)sy);
  // line(0,(double)y-(double)sy/2 + ((double)x*(double)sy)/(double)sx,1000,(double)y-(double)sy/2 + (1000*(double)sy)/(double)sx - ((double)x*(double)sy)/(double)sx);
 //  line(0,(double)y-(double)sy/2 + ((double)x*(double)sy)/(double)sx + (double)sy,1000,(double)y-(double)sy/2 + (1000*(double)sy)/(double)sx - ((double)x*(double)sy)/(double)sx + (double)sy);
   if((mousey() >= (double)y+(double)sy/2 - ((double)mousex()*(double)sy)/(double)sx + ((double)x*(double)sy)/(double)sx) &&
      (mousey() <= (double)y+(double)sy/2 - ((double)mousex()*(double)sy)/(double)sx + ((double)x*(double)sy)/(double)sx +(double)sy) &&
   (mousey() >= (double)y-(double)sy/2 + ((double)mousex()*(double)sy)/(double)sx - ((double)x*(double)sy)/(double)sx) &&
   (mousey() <= (double)y-(double)sy/2 + ((double)mousex()*(double)sy)/(double)sx - ((double)x*(double)sy)/(double)sx + (double)sy) && (mousebuttons() == 1))
   {
      return (1);
   }
   else return (0);
}

void parl(int x, int y, int sizex, int sizey, int tcol)
   {
      if(tcol == 1)
      setcolor(RED);
   else
      setcolor(BLACK);
   line(x + 10,y,x+sizex,y);
   line(x + 10,y,x,y + sizey);
   line(x+sizex,y,x + sizex - 10,y + sizey);
   line(x,y + sizey,x+sizex - 10,y + sizey);
   }
   
   int testparl(int x, int y, int sx, int sy)
{
   if((mousey() >= y) &&
      (mousey() <= y + sy) &&
   (mousey() >= (double)y - ((double)mousex()*(double)sy)/(double)10 + ((double)x*(double)sy)/(double)10 + (double)sy) &&
   (mousey() <= (double)y - ((double)mousex()*(double)sy)/(double)10 + ((double)x*(double)sy)/(double)10 + (double)sy*(double)sx/(double)10) && (mousebuttons() == 1))
   {
      return (1);
   }
   else return (0);
}

void arr(int x1,int y1, int x2, int y2,int tcol)
{
   double fi;
   if(tcol == 1)
    setcolor(RED);
   else
      setcolor(BLACK);
   line(x1,y1,x2,y2);
   int a[6] = {x2,y2},b[6] = {x2,y2},dy =y2 - y1,dx = x2 -x1;
   if(x1 == x2)
   {
      if(dy > 0)
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
   else if(y1 == y2)
   {
      if(dx > 0)
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
   else if(dx > 0)
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
    if(tcol == 1)
    setfillstyle(SOLID_FILL,RED);
   else
      setfillstyle(SOLID_FILL,BLACK);
   fillpoly(3, a);
   fillpoly(3, b);
}

void drawarrow(arrow arro, int tcol)
{
   arr(arro.x1,arro.y1,arro.x2,arro.y2,tcol);
   int dx = arro.x2 - arro.x1, dy = arro.y2 - arro.y1;
   setbkmode(TRANSPARENT);
   setcolor(BLACK);
   settextjustify(LEFT_TEXT,TOP_TEXT);
   if(dx > 0)
   {
       if(dy>=0)
      {
         outtextxy((arro.x1 + arro.x2)/2 + 5,(arro.y1 + arro.y2)/2 - 5,arro.text);
      }
      else
      {
         outtextxy((arro.x1 + arro.x2)/2 + 5,(arro.y1 + arro.y2)/2 + 10,arro.text);
      }
   }
   else
   {
       if(dy>=0)
      {
         outtextxy((arro.x1 + arro.x2)/2 + 5,(arro.y1 + arro.y2)/2 - 5,arro.text);
      }
      else
      {
         outtextxy((arro.x1 + arro.x2)/2 + 5,(arro.y1 + arro.y2)/2 + 10,arro.text);
      }
   }
}

void drawobj(obj ob,int tcol)
{
   switch(ob.t)
   {
      case(KVAD):
         kvad(ob.x,ob.y,ob.sizex,ob.sizey,tcol);
         break;
      case(SKVAD):
         skvad(ob.x,ob.y,ob.sizex,ob.sizey,tcol);
        break;
      case(ROMB):
         romb(ob.x,ob.y,ob.sizex,ob.sizey,tcol);
         //tes(ob.x,ob.y,ob.sizex,ob.sizey);
         //tes(ob.x,ob.y,ob.sizex,ob.sizey);
        break;
      case(PARL):
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

void drawallobjects()
{
   for(int i = 0; i < kolobj; i++)
   {
      if(i == nomobj  && actoa && typeoa == 1)
         drawobj(objm[i],1);
      else
         drawobj(objm[i],0);
   }
}

void drawallarrows()
{
   for(int i = 0; i < kolarr;i++)
   {
      if(i == nomarr && actoa && typeoa == 2)
         drawarrow(arrm[i],1);
      else
         drawarrow(arrm[i],0);
   }
}

void addobject(objtype t)
{
   if(kolobj < 100)
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
      for(int i = 0 ;i < 101; i++)
      {
         objm[nomobj].text[i] = a[i];
         if(a[i] == '\0') break;
      }
   }
}

void addarrow()
{
   if(kolarr < 100)
   {
      
      actoa = 1;
      typeoa = 2;
      kolarr++;
      nomarr = kolarr-1;
      arrm[nomarr].x1 = getmaxx()/2;
      arrm[nomarr].y1 = getmaxy()/2;
      arrm[nomarr].x2 = getmaxx()/2+100;
      arrm[nomarr].y2 = getmaxy()/2+100;
      char a[101] = "Текст\0";
      for(int i = 0 ;i < 101; i++)
      {
         arrm[nomarr].text[i] = a[i];
         if(a[i] == '\0') break;
      }
   }
}

int buttonobj(int left,int top, int right,int bottom,void (*f)(objtype), objtype t)
{
   if(mousex() >= left && mousex() <= right && mousey() >= top && mousey() <= bottom && mousebuttons() == 1)
   {
      //printf("1");
      f(t);
      delay(100);
      return(1);
   }
   else return (0);
}

int button(int left,int top, int right,int bottom,void (*f)())
{
   if(mousex() >= left && mousex() <= right && mousey() >= top && mousey() <= bottom && mousebuttons() == 1)
   {
      f();
      delay(100);
      return(1);
   }
   else return (0);
}

void testallobjects()
{
   int j;
   for(int i = 0; i < kolobj; i++)
   {
      switch(objm[i].t)
      {
         case(KVAD):
         j = testkvad(objm[i].x,objm[i].y,objm[i].sizex,objm[i].sizey);
         break;
      case(SKVAD):
         j = testskvad(objm[i].x,objm[i].y,objm[i].sizex,objm[i].sizey);
        break;
      case(ROMB):
         j = testromb(objm[i].x,objm[i].y,objm[i].sizex,objm[i].sizey);
        break;
      case(PARL):
         j = testparl(objm[i].x,objm[i].y,objm[i].sizex,objm[i].sizey);
         break;
      }
      if(j)
      {
         actoa = 1;
         typeoa = 1;
         nomobj = i;
         return;
      }
   }
   return;
}

int inpactobj()
{
   int a;
   if(kbhit())
   {
      a = getch();
      if(a == 0)
      {
         a = getch();
         switch(a)
         {
            case(KEY_LEFT):
               objm[nomobj].x--;
               return(1);
            case(KEY_RIGHT):
               objm[nomobj].x++;
               return(1);
            case(KEY_UP):
               objm[nomobj].y--;
               return(1);
            case(KEY_DOWN):
               objm[nomobj].y++;
               return(1);
         }
      }
   }
   if(mousex() >= 15 && mousey() >= 320 && mousex() <= 61 && mousey() <= 341 && mousebuttons() == 1)
         {
            if(objm[nomobj].sizex > 50) objm[nomobj].sizex--;
               return(1);
         }
         if(mousex() >= 94 && mousey() >= 320 && mousex() <= 140 && mousey() <= 341 && mousebuttons() == 1)
         {
            if(objm[nomobj].sizex < 500 && objm[nomobj].sizex + objm[nomobj].x <= 788) objm[nomobj].sizex++;
               return(1);
         }
         if(mousex() >= 15 && mousey() >= 374 && mousex() <= 61 && mousey() <= 395 && mousebuttons() == 1)
         {
            if(objm[nomobj].sizey > 50) objm[nomobj].sizey--;
               return(1);
         }
         if(mousex() >= 94 && mousey() >= 374 && mousex() <= 140 && mousey() <= 395 && mousebuttons() == 1)
         {
            if(objm[nomobj].sizey < 500 && objm[nomobj].sizey + objm[nomobj].y <= 588) objm[nomobj].sizey++;
               return(1);
         }
         if(mousex() >= 153 && mousey() >= 59 && mousex() <= 788 && mousey() <= 588 && mousebuttons() == 2)
         {
            objm[nomobj].x = mousex() - objm[nomobj].sizex/2;
            objm[nomobj].y = mousey() - objm[nomobj].sizey/2;
            if(objm[nomobj].x < 153) objm[nomobj].x = 153;
            if(objm[nomobj].y < 59) objm[nomobj].y = 59;
            if(objm[nomobj].x + objm[nomobj].sizex > 788) objm[nomobj].x = 788 - objm[nomobj].sizex;
            if(objm[nomobj].y + objm[nomobj].sizey > 588) objm[nomobj].y = 588 - objm[nomobj].sizey;
            return (1);
         }
   return(0);
}



void Setup()
{
   actoa =0;
   typeoa = 0;
   nomobj = 0;
   nomarr = 0;
   kolobj = 0;
   kolarr = 0;
   typearrow = 0;
   MAIN = loadBMP("MAIN.jpg");
}

void Input()
{
   if(actoa == 1)
   {
      if(typeoa == 1)
      {
         if(inpactobj() == 1) return;
      }
      else if(typeoa == 2)
      {
         ;
      }
   }
   testallobjects();
  if(buttonobj(1,77,150,113,addobject,KVAD) == 1) return;
  if(buttonobj(1,115,150,153,addobject,PARL)) return;
  if(buttonobj(1,155,150,193,addobject,ROMB)) return;
  if(buttonobj(1,195,150,234,addobject,SKVAD)) return;
  if(button(1,236,150,273,addarrow)) return;
}

void Draw()
{
   p = 1 - p;
   setactivepage(p);
   clearviewport();
   putimage(0, 0, MAIN, OR_PUT);
   drawallobjects();
   drawallarrows();
   setvisualpage(p);
}

int main()
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
