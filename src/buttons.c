#include "../include/mazegame.h"

/**
 * buttonUp - Key released
 * @key: char keys to be released
 * @x: int to print
 * @y: int to print
 * returns: release keys when called
 */

void buttonUp(unsigned char key, int x, int y)
{
	if (key == 'a')
	{ Keys.a = 0; }

	if (key == 'd')
	{ Keys.d = 0; }

	if (key == 'w')
	{ Keys.w = 0; }

	if (key == 's')
	{ Keys.s = 0; }

	glutPostRedisplay();
}

/**
 * buttonDown - key pressed
 * @key: char key to be pressed
 * @x: int to print
 * @y: int to print
 * returns: press keys when called
 */

void buttonDown(unsigned char key, int x, int y)
{
	if (key == 'a')
	{ Keys.a = 1; }

	if (key == 'd')
	{ Keys.d = 1; }

	if (key == 'w')
	{ Keys.w = 1; }

	if (key == 's')
	{ Keys.s = 1; }

	if (key == 'o')	/**open doors**/
	{
		int xo = 0;

		if (pdx < 0)
		{ xo = -25; }
		else
		{ xo = 25; }

		int yo = 0;

		if (pdy < 0)
		{ yo = -25; }
		else
		{ yo = 25; }

		int ipx = px / 64.0,	ipx_add_xo = (px + xo) / 64.0;
		int ipy = py / 64.0,	ipy_add_yo = (py + yo) / 64.0;

		if (mapW[ipy_add_yo * mapX + ipx_add_xo] == 4)
		{
			mapW[ipy_add_yo * mapX + ipx_add_xo] = 0;
		}
	}
	glutPostRedisplay();
}
