#include "gl/glut.h"

void display() {
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f, -0.2f);
    glVertex2f(0.2f, -0.2f);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(-0.2f, 0.2f);
    glEnd();
    glFinish();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("glut Å×½ºÆ®");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}