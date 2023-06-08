#include "../include/mazegame.h"

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 510);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("MAZEGAME");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(buttonDown);
    glutKeyboardUpFunc(buttonUp);
    glutMainLoop();
}
