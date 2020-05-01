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
   if(tcol = 1)
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
    if(tcol = 1)
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
   if(tcol = 1)
      setcolor(RED);
   else
      setcolor(BLACK);
   line(x + sizex/2,y,x+sizex,y + sizey/2);
   line(x + sizex/2,y,x,y + sizey/2);
   line(x + sizex/2,y + sizey,x+sizex,y + sizey/2);
   line(x + sizex/2,y + sizey,x,y + sizey/2);
}

int testromb(int x, int y, int sx, int sy)
{
   if((mousex() >= (double)y+(double)sy/2 - ((double)mousex()*(double)sy)/(double)sx + ((double)x*(double)sy)/(double)sx) &&
      (mousex() <= (double)y+(double)sy/2 - ((double)mousex()*(double)sy)/(double)sx + ((double)x*(double)sy)/(double)sx +(double)sy) &&
   (mousex() >= (double)y-(double)sy/2 + ((double)mousex()*(double)sy)/(double)sx - ((double)x*(double)sy)/(double)sx) &&
   (mousex() <= (double)y-(double)sy/2 + ((double)mousex()*(double)sy)/(double)sx - ((double)x*(double)sy)/(double)sx + (double)sy) && (mousebuttons() == 1))
   {
      return (1);
   }
   else return (0);
}

void parl(int x, int y, int sizex, int sizey, int tcol)
   {
      if(tcol = 1)
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
   if(tcol = 1)
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
   fillpoly(3, a);
   fillpoly(3, b);
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
   
}

void Draw()
{
   p = 1 - p;
   setactivepage(p);
   clearviewport();
   putimage(0, 0, MAIN, OR_PUT);
   arr(getmaxx()/2,getmaxy()/2,mousex(),mousey(),0);
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
