#include <stdio.h> // Объявление библиотек
#include <stdarg.h>
#include <math.h>
#include "glut.h"
#include <iostream>
#include <stdlib.h>

GLint Width = 1000, Height = 1000; // Размер окна

#define ESCAPE '\033' // Выход

char command = '/0'; // Объявление переменных

int R, G, B, xF, xS, yF, yS;

int sign(int x) // Погрешность
{
    if (x > 0)    {
        return 1;
    }

    if (x < 0){
        return -1;
    }
    return 0;
}

float sign(float x) // Погрешность
{
    if (x > 0){
        return 1;
    }
    if (x < 0){
        return -1;
    }
    return 0;
}

void Brezenhem(int x1, int y1, int x2, int y2, int R, int G, int B, int A) // Метод Брезенхема
{
    glEnable(GL_BLEND); // Расширение

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int i, Px, Py, E, Sx, Sy;

    float X, Y;

    glPointSize(20); // Размер точек

    glColor4ub(R, G, B, A); // Цвет линии

    X = x1;

    Y = y1;

    Px = abs(x2 - x1); // Координаты относительно прямой

    Py = abs(y2 - y1);

    Sy = sign(y2 - y1);

    Sx = sign(x2 - x1);

    bool PxGrPy = Px > Py ? true : false; // Проверка

    if (!PxGrPy) // Редактирование искажений

    {

        int temp = Px;

        Px = Py;

        Py = temp;

    }

    E = 2 * Py - Px;

    for (int i = 0; i <= Px; i++)

    {

        glBegin(GL_POINTS);

        glVertex2f(X + 0.5 * (float)Sx, Y + 0.5 * (float)Sy); // Построение точек относительно прямой

        glEnd();

        if (PxGrPy)

        {

            if (E <= 0)

            {

                X = X + Sx;

                E = E + 2 * Py;

            }

            else

            {

                X = X + Sx;

                Y = Y + Sy;

                E = E + 2 * (Py - Px);

            }

        }

        else

        {

            if (E <= 0)

            {

                Y = Y + Sy;

                E = E + 2 * Py;

            }

            else

            {

                X = X + Sx;

                Y = Y + Sy;

                E = E + 2 * (Py - Px);

            }

        }

    };

    glLineWidth(5); // Толщина прямой

    glBegin(GL_LINES);

    glColor3ub(0, -89, 128); // Цвет прямой

    glVertex2f(x1, y1); // Координаты

    glVertex2f(x2, y2);

    glEnd();

    glFinish();

}

void CDA(int x1, int y1, int x2, int y2, int R, int G, int B, int A) // Метод ЦДА

{

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(20); // Размер точек

    glColor4ub(R, G, B, A);

    float x, y, Px, Py;

    int i, len;

    if (abs(x2 - x1) >= abs(y2 - y1))

    {

        len = abs(x2 - x1);

    }

    else

        len = abs(y2 - y1);

    Px = ((float)x2 - (float)x1) / (float)len;

    Py = ((float)y2 - (float)y1) / (float)len;

    x = (float)x1;

    y = (float)y1;

    float tempx = x;

    float tempy = y;

    i = 1;

    while (i <= len + 1)

    {

        glBegin(GL_POINTS);

        glVertex2f(x + 0.5 * sign(Px), y + 0.5 * sign(Py)); // Смещение осей

        glEnd();

        tempx = tempx + Px;

        x = floor(tempx);

        tempy = tempy + Py;

        y = floor(tempy);

        i = i + 1;

    }

    glLineWidth(5);

    glBegin(GL_LINES);

    glColor3ub(100, 0, 0);

    glVertex2f(x1, y1);

    glVertex2f(x2, y2);

    glEnd();

}

void Display() // Взаимодейстивие с программой

{

    glLineWidth(1);

    glClearColor(1, 1, 1, 1);

    glClear(GL_COLOR_BUFFER_BIT);

    int Width, Height;

    for (Width = -20; Width <= 20; Width++)

    {

        glBegin(GL_LINES);

        glColor3b(0, 0, 0);

        glVertex2f(Width, 20);

        glVertex2f(Width, -20);

        glEnd();

    }

    for (Height = 20; Height >= -20; Height--)

    {

        glBegin(GL_LINES);

        glColor3b(0, 0, 0);

        glVertex2f(-20, Height);

        glVertex2f(20, Height);

        glEnd();

    }

    glLineWidth(5);

    glBegin(GL_LINES);

    glColor3ub(0, 200, 0);

    glVertex2f(0, Height);

    glVertex2f(0, -Height);

    glEnd();

    glLineWidth(5);

    glBegin(GL_LINES);

    glColor3ub(0, 1, 0); // Цвет оси OX

    glVertex2f(Width, 0);

    glVertex2f(-Width, 0);

    glEnd();

    int x1, x2, y1, y2;

    std::cout << "Incert coords:";

    std::cin >> x1 >> y1 >> x2 >> y2;

    Brezenhem(x1, y1, x2, y2, 100, 100, 0, 128);

    CDA(x1, y1, x2, y2, 155, 69, 0, 128);

    glFinish();

}

void main(int argc, char* argv[]) // Тело программы

{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowSize(Width, Height);

    glutCreateWindow("GENERATION OF VECTORS"); // Название

    glOrtho(-20, 20, -20, 20, -20, 20);

    glutDisplayFunc(Display);

    glutMainLoop();

}
