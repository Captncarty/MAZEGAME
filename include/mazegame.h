#ifndef _MAZEGAME_H_
#define _MAZEGAME_H_
#define GL_SILENCE_DEPRECATION

#define mapX  8      /***map width***/
#define mapY  8      /***map height***/
#define mapS 64      /***map cube size***/

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

extern int mapW[];
extern int myTextures[];
extern int mapF[];
extern int mapC[];

float getRad(float a);
float fixAngle(float a);
float distance(float ax, float ay, float bx, float by, float ang);
float px, py, pdx, pdy, pa;
float frame1, frame2, fps;
int main(int argc, char *argv[]);
void resize(int w, int h);
void buttonUp(unsigned char key, int x, int y);
void buttonDown(unsigned char key, int x, int y);
void display(void);
void init(void);
void drawRays(void);
void drawPlayer(void);
void drawMap(void);


/**
 * struct ButtonKeys- control keys
 * @w: up key
 * @a: right key
 * @d: left key
 * @s: down key
 **/

typedef struct ButtonKeys
{
int w, a, d, s;                     /***button state on off***/
} Buttons;
Buttons Keys;

#endif /* MAZEGAME_H */
