#include "../include/mazegame.h"

void init(){
    glClearColor(0.5, 0, 0.5, 0);
    gluOrtho2D(0, 1024, 510, 0);
    px = 150;   py = 400;   pa = 90;
    pdx = cos(getRad(pa));  pdy = -sin(getRad(pa));
}
