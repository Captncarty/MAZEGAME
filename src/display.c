#include "../include/mazegame.h"

//convert to radian
float getRad(float a){
    return a*M_PI / 180.0;
}

//correct angles
float fixAngle(float a){
    if (a > 359){
        a -= 360;
    }
    if (a < 0){
        a += 360;
    }
    return a;
}

//calculate distance
float distance(float ax,float ay,float bx,float by,float ang){
    return cos( getRad(ang)) * (bx-ax) - sin( getRad(ang)) * (by-ay);
}

void display(){
    //frames per second
    frame2 = glutGet(GLUT_ELAPSED_TIME);    fps = (frame2 - frame1);    frame1 = glutGet(GLUT_ELAPSED_TIME);

    /***Buttons***/
    if (Keys.a == 1){ pa += 0.2*fps;    pa = fixAngle(pa);  pdx = cos(getRad(pa));  pdy = -sin(getRad(pa));}
    if (Keys.d == 1){ pa -= 0.2*fps;    pa = fixAngle(pa);  pdx = cos(getRad(pa));  pdy = -sin(getRad(pa));}

    //x offset to check map
    int xo = 0;
    if (pdx < 0){
        xo=-20;
    }else {
        xo = 20;
    }

    //y offset to check map
    int yo = 0;
    if (pdy < 0){
        yo=-20;
    }else {
        yo = 20;
    }

    int ipx = px/64.0,  ipx_add_xo = (px + xo)/64.0,    ipx_sub_xo = (px - xo)/64.0;    //x pos and offset
    int ipy = py/64.0,  ipy_add_yo = (py + yo)/64.0,    ipy_sub_yo = (py - yo)/64.0;    //y pos and offset

    /***Move Forward***/
    if (Keys.w == 1){
        if (mapW[ipy*mapX + ipx_add_xo] == 0){ px += pdx*0.2*fps;}
        if (mapW[ipy_add_yo * mapX + ipx] == 0){ py += pdy*0.2*fps;}
    }

    /***move downward***/
    if (Keys.s == 1){
        if (mapW[ipy*mapX + ipx_sub_xo] == 0){ px -= pdx*0.2*fps;}
        if (mapW[ipy_sub_yo * mapX + ipx] == 0){ py -= pdy*0.2*fps;}
    }

    glutPostRedisplay();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawMap();
    drawPlayer();
    drawRays();
    glutSwapBuffers();
}

void resize(int w, int h)
{
    glutReshapeWindow(1054, 512);
}
