#include "../include/mazegame.h"

void drawPlayer(){
    glColor3f(0,1,1);
    glPointSize(8);
    glLineWidth(4);

    glBegin(GL_POINTS);
    glVertex2i(px, py);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(px, py);
    glVertex2i(px+pdx*20, py+pdy*20);
    glEnd();
}
