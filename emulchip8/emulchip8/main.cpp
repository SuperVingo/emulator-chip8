#include "chip8.h"
#include "gl/glut.h"

// Chip 8
Chip8 chip;

// 1 Pixel => 10x10 Rectangle
#define PIXEL 10

void drawScreen() 
{
    // Display Function
    for (int y = 0; y < 64; y++)
    {
        for (int x = 0; x < 32; x++)
        {
            if (chip.gfx[y * 64 + x] == 1)
            {
                glBegin(GL_QUADS);
                glVertex3f(x, y, 0.0);
                glVertex3f(x, y + PIXEL, 0.0);
                glVertex3f(x + PIXEL, y + PIXEL, 0.0);
                glVertex3f(x + PIXEL, y, 0.0);
                glEnd();
            }
        }
    }
}

int main(int argc, char** argv)
{
    // Load Program


    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(64 * PIXEL, 32 * PIXEL);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Chip 8 Emulator - Screen");
    
    // Event Function
    glutDisplayFunc(mainLoop);
    glutKeyboardFunc(KeyboardDown);
    glutKeyboardUpFunc(KeyboardUp);

    glutMainLoop();

    return 0;
}

void mainLoop()
{
    chip.ChipCycle();

    if (chip.drawFlag)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        drawScreen();

        glutSwapBuffers();

        chip.drawFlag = false;
    }
}

void KeyboardDown(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);

    switch (key)
    {
    case '1': { chip.key[0x0] = 1; break; }
    case '2': { chip.key[0x1] = 1; break; }
    case '3': { chip.key[0x2] = 1; break; }
    case '4': { chip.key[0x3] = 1; break; }
    case 'q': { chip.key[0x4] = 1; break; }
    case 'w': { chip.key[0x5] = 1; break; }
    case 'e': { chip.key[0x6] = 1; break; }
    case 'r': { chip.key[0x7] = 1; break; }
    case 'a': { chip.key[0x8] = 1; break; }
    case 's': { chip.key[0x9] = 1; break; }
    case 'd': { chip.key[0xa] = 1; break; }
    case 'f': { chip.key[0xb] = 1; break; }
    case 'z': { chip.key[0xc] = 1; break; }
    case 'x': { chip.key[0xd] = 1; break; }
    case 'c': { chip.key[0xe] = 1; break; }
    case 'v': { chip.key[0xf] = 1; break; }
    }
}

void KeyboardUp(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1': { chip.key[0x0] = 0; break; }
    case '2': { chip.key[0x1] = 0; break; }
    case '3': { chip.key[0x2] = 0; break; }
    case '4': { chip.key[0x3] = 0; break; }
    case 'q': { chip.key[0x4] = 0; break; }
    case 'w': { chip.key[0x5] = 0; break; }
    case 'e': { chip.key[0x6] = 0; break; }
    case 'r': { chip.key[0x7] = 0; break; }
    case 'a': { chip.key[0x8] = 0; break; }
    case 's': { chip.key[0x9] = 0; break; }
    case 'd': { chip.key[0xa] = 0; break; }
    case 'f': { chip.key[0xb] = 0; break; }
    case 'z': { chip.key[0xc] = 0; break; }
    case 'x': { chip.key[0xd] = 0; break; }
    case 'c': { chip.key[0xe] = 0; break; }
    case 'v': { chip.key[0xf] = 0; break; }
    }
}