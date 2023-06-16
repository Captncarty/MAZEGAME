#include "../include/mazegame.h"

/**
 * drawRays - draws rays
 * returns: set of rays when called
 */


void drawRays(void)
{
	glColor3f(0, 1, 1);
	glBegin(GL_QUADS);
	glVertex2i(526, 0);
	glVertex2i(1006, 0);
	glVertex2i(1006, 160);
	glVertex2i(526, 160);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_QUADS);
	glVertex2i(526, 160);
	glVertex2i(1006, 160);
	glVertex2i(1006, 320);
	glVertex2i(526, 320);
	glEnd();

	int r, mx, my, mp, dof, side;
	float vx, vy, rx, ry, ra, xo, yo, disV, disH;

	/**set ray back by 30degrees**/
	ra = fixAngle(pa + 30);

	for (r = 0; r < 60; r++)
	{
		int vmt = 0,	hmt = 0;	/**map texture num**/

		/***Vertical***/
		dof = 0;
		side = 0;
		disV = 100000;

		float Tan = tan(getRad(ra));

		if (cos(getRad(ra)) > 0.001)
		{
			rx = (((int)px >> 6) << 6) + 64;
			ry = (px - rx) * Tan + py;
			xo = 64;
			yo = -xo * Tan;	/**look left**/
		} else if (cos(getRad(ra)) <  -0.001)
		{
			rx = (((int)px >> 6) << 6) - 0.0001;
			ry = (px - rx) * Tan + py;
			xo = -64;
			yo = -xo * Tan;	/**look right**/
		} else
		{
			rx = px;
			ry = py;
			dof = 8;	/**no hit**/
		}

		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * mapX + mx;

			if (mp > 0 && mp < mapX * mapY && mapW[mp] > 0)
			{
				vmt = mapW[mp] - 1;
				dof = 8;
				disV = cos(getRad(ra)) * (rx - px) - sin(getRad(ra)) * (ry - py);	/**hit**/
			} else
			{
				rx += xo;
				ry += yo;
				dof += 1;	/**next horizontal**/
			}
		}

		vx = rx;
		vy = ry;

		/***Horizontal***/
		dof = 0;
		disH = 100000;
		Tan = 1.0 / Tan;

		if (sin(getRad(ra)) > 0.001)
		{
			ry = (((int)py >> 6) << 6) - 0.0001;
			rx = (py - ry) * Tan + px;
			yo = -64;
			xo = -yo * Tan;	/**look up**/
		} else if (sin(getRad(ra)) < -0.001)
		{
			ry = (((int)py >> 6) << 6) + 64;
			rx = (py - ry) * Tan + px;
			yo = 64;
			xo = -yo * Tan;	/**look down**/
		} else
		{
			rx = px;
			ry = py;
			dof = 8;
		}

		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && mapW[mp] > 0)
			{
				hmt = mapW[mp] - 1;
				dof = 8;
				disH = cos(getRad(ra)) * (rx - px) - sin(getRad(ra)) * (ry - py);	/**hit**/
			} else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}	/**next horizontal**/
		}

		float shade = 1;

		glColor3f(0, 0.8, 0);

		if (disV < disH)
		{
			hmt = vmt;
			shade = 0.5;
			rx = vx;
			ry = vy;
			disH = disV;
			glColor3f(0, 0.6, 0);
		}	/**horizontal hit**/

		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex2i(px, py);
		glVertex2i(rx, ry);
		glEnd();	/**draw 2D ray**/

		int ca = fixAngle(pa - ra);

		disH = disH * cos(getRad(ca));	/**fix fisheye**/

		int lineH = (mapS * 320) / (disH);
		float ty_step = 32.0 / (float)lineH;
		float ty_off = 0;

		if (lineH > 320)
		{
			ty_off = (lineH - 320) / 2.0;
			lineH = 320;
		}	/**line height n limit**/

		int lineOff = 160 - (lineH >> 1);	/**offset**/


		/***draw Walls***/
		int y;
		float ty = ty_off * ty_step + hmt * 32;
		float tx;

		if (shade == 1)
		{
			tx = (int)(rx / 2.0) % 32;
			if (ra > 180)
			{
				tx = 31 - tx;
			}
		}

		for (y = 0; y < lineH; y++)
		{
			float c = myTextures[(int)(ty) * 32 + (int)(tx)] * shade;

			if (hmt == 0)
			{ glColor3f(c, c / 2.0, c / 2.0); } /**checkerboard red**/
			if (hmt == 1)
			{ glColor3f(c, c, c / 2.0); } /**brick yellow**/
			if (hmt == 2)
			{ glColor3f(c / 2.0, c / 2.0, c); } /**window blue**/
			if (hmt == 3)
			{ glColor3f(c / 2.0, c, c / 2.0); } /**door green**/

			glPointSize(8);
			glBegin(GL_POINTS);
			glVertex2i(r * 8 + 530, y + lineOff);
			glEnd();	/**draw vertical wall**/

			ty += ty_step;
		}

		/***draw floors***/
		for (y = lineOff + lineH; y < 320; y++)
		{
			float dy = y - (320 / 2.0), deg = getRad(ra),	raFix = cos(getRad(fixAngle(pa - ra)));

			tx = px / 2 + cos(deg) * 158 * 32 / dy / raFix;
			ty = py / 2 - sin(deg) * 158 * 32 / dy / raFix;
			int mp = mapF[(int)(ty / 32.0) * mapX + (int)(tx / 32.0)] * 32 * 32;
			float c = myTextures[((int)(ty) & 31) * 32 + ((int)(tx) & 31) + mp] * 0.7;

			glColor3f(c / 1.3, c / 1.3, c);
			glPointSize(8);
			glBegin(GL_POINTS);
			glVertex2i(r * 8 + 530, y);
			glEnd();

			/***draw ceiling***/
			mp = mapC[(int)(ty / 32.0) * mapX + (int)(tx / 32.0)] * 32 * 32;
			c = myTextures[((int)(ty) & 31) * 32 + ((int)(tx) & 31) + mp] * 0.7;
			glColor3f(c / 2.0, c / 1.2, c / 2.0);
			glPointSize(8);
			glBegin(GL_POINTS);
			glVertex2i(r * 8 + 530, 320 - y);
			glEnd();
		}
		ra = fixAngle(ra - 1);	/**next ray, total: 60**/
	}
}
