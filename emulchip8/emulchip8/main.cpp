#include "chip8.h"
#include "gl/glut.h"

// Chip 8
Chip8 chip;

// 1 Pixel => 10x10 Rectangle
#define PIXEL 10

void mainLoop();
void drawScreen();
void KeyboardDown(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);

int main(int argc, char** argv)
{
    // Initialize and Load Program
    chip.Initialize();
    if (!chip.LoadProgram("prog.c8"))
        return 0;

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(64 * PIXEL, 32 * PIXEL);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Chip 8 Emulator - Screen");
    
    // Event Function
    glutDisplayFunc(mainLoop);
    glutIdleFunc(mainLoop);
    glutKeyboardFunc(KeyboardDown);
    glutKeyboardUpFunc(KeyboardUp);

    glutMainLoop();

    return 0;
}

void drawScreen()
{
    system("cls");
    for (int y = 0; y < 32; y++)
    {
        for (int x = 0; x < 64; x++)
        {
            if (chip.gfx[y * 64 + x] == 1)
            {
                printf("o");
            } 
            else
            {
                printf(".");
            }
        }
        printf("\n");
    }
    // Display Function
    for (int y = 0; y < 32; y++)
    {
        for (int x = 0; x < 64; x++)
        {
            if (chip.gfx[y * 64 + x] == 0)
                glColor3f(0.0f, 0.0f, 0.0f);
            else
                glColor3f(1.0f, 0.50f, 1.0f);

            glBegin(GL_QUADS);
            
            glVertex3f(-1.0f + (x * 0.03125f), -(-1.0f + (y * 0.0625f)), 0.0f);
            
            glVertex3f(-1.0f + (x * 0.03125f), -(-1.0f + (y * 0.0625f) + 0.0625f), 0.0f);
            
            glVertex3f(-1.0f + (x * 0.03125f) + 0.03125f, -( - 1.0f + (y * 0.0625f) + 0.0625f), 0.0f);
            
            glVertex3f(-1.0f + (x * 0.03125f) + 0.03125f, -(-1.0f + (y * 0.0625f)), 0.0f);
            
            glEnd();
        }
    }
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
    case '1': { chip.key[0x1] = 1; break; }
    case '2': { chip.key[0x2] = 1; break; }
    case '3': { chip.key[0x3] = 1; break; }
    case '4': { chip.key[0xC] = 1; break; }
    case 'q': { chip.key[0x4] = 1; break; }
    case 'w': { chip.key[0x5] = 1; break; }
    case 'e': { chip.key[0x6] = 1; break; }
    case 'r': { chip.key[0xD] = 1; break; }
    case 'a': { chip.key[0x7] = 1; break; }
    case 's': { chip.key[0x8] = 1; break; }
    case 'd': { chip.key[0x9] = 1; break; }
    case 'f': { chip.key[0xE] = 1; break; }
    case 'z': { chip.key[0xA] = 1; break; }
    case 'x': { chip.key[0x0] = 1; break; }
    case 'c': { chip.key[0xB] = 1; break; }
    case 'v': { chip.key[0xF] = 1; break; }
    }
}

void KeyboardUp(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1': { chip.key[0x1] = 0; break; }
    case '2': { chip.key[0x2] = 0; break; }
    case '3': { chip.key[0x3] = 0; break; }
    case '4': { chip.key[0xC] = 0; break; }
    case 'q': { chip.key[0x4] = 0; break; }
    case 'w': { chip.key[0x5] = 0; break; }
    case 'e': { chip.key[0x6] = 0; break; }
    case 'r': { chip.key[0xD] = 0; break; }
    case 'a': { chip.key[0x7] = 0; break; }
    case 's': { chip.key[0x8] = 0; break; }
    case 'd': { chip.key[0x9] = 0; break; }
    case 'f': { chip.key[0xE] = 0; break; }
    case 'z': { chip.key[0xA] = 0; break; }
    case 'x': { chip.key[0x0] = 0; break; }
    case 'c': { chip.key[0xB] = 0; break; }
    case 'v': { chip.key[0xF] = 0; break; }
    }
}