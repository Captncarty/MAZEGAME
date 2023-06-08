#include "../include/mazegame.h"

int mapW[]=          //walls
{
 1,1,1,1,1,3,1,1,
 1,0,0,1,0,0,0,1,
 1,0,0,4,0,2,0,1,
 1,1,4,1,0,0,0,1,
 2,0,0,0,0,0,0,1,
 2,0,0,0,0,2,0,1,
 2,0,0,0,0,0,0,1,
 1,1,3,1,3,1,3,1,
};

int mapF[]=          //floors
{
 0,0,0,0,0,0,0,0,
 0,0,0,0,1,1,0,0,
 0,0,0,0,2,0,0,0,
 0,0,0,0,0,0,0,0,
 0,0,2,0,0,0,0,0,
 0,0,0,0,0,0,0,0,
 0,1,1,1,1,0,0,0,
 0,0,0,0,0,0,0,0,
};

int mapC[]=          //ceiling
{
 0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,1,0,
 0,1,1,1,0,0,0,0,
 0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,
};

void drawMap()
{
 int x,y,xo,yo;
 for(y=0;y<mapY;y++)
 {
  for(x=0;x<mapX;x++)
  {
   if(mapW[y*mapX+x]>0){ glColor3f(1,1,1);} else{ glColor3f(0,0,0);}
   xo=x*mapS; yo=y*mapS;
   glBegin(GL_QUADS);
   glVertex2i( 0   +xo+1, 0   +yo+1);
   glVertex2i( 0   +xo+1, mapS+yo-1);
   glVertex2i( mapS+xo-1, mapS+yo-1);
   glVertex2i( mapS+xo-1, 0   +yo+1);
   glEnd();
  }
 }
}
