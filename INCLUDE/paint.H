#ifndef PAINT_H
#define PAINT_H

/*librerias necesarias*/
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <stdlib.h>
#include <time.h>

union REGS inm, outm;

/*prototipo*/
int mouse_init();
void showe_mouse();
void hide_mouse();
void get_mouse_status(int *button, int *x, int *y);
void move_mouse(int x, int y);
int color_click(int x, int y);
int salir_click(int x, int y);
void all_funtion();
void funcion_paint();

/*funciones mouse*/
int mouse_init()
{
    inm.x.ax = 0;
    int86(0x33, &inm, &outm);
    return outm.x.ax;
}
void showe_mouse()
{
    inm.x.ax = 1;
    int86(0x33, &inm, &outm);
}
void hide_mouse()
{
    inm.x.ax = 2;
    int86(0x33, &inm, &outm);
}
void get_mouse_status(int *button, int *x, int *y)
{
    inm.x.ax = 3;
    int86(0x33, &inm, &outm);
    *button = outm.x.bx;
    *x = outm.x.cx;
    *y = outm.x.dx;
}

void move_mouse(int x, int y) {
	inm.x.ax = 4;
	inm.x.cx = x;
	inm.x.dx = y;
	int86(0x33, &inm, &outm);
}

#define AREA_X1 96
#define AREA_Y1 97
#define AREA_X2 639
#define AREA_Y2 479

int current_color = 0;
int prev_selected_color_code = 0;

/*cuadro de colores y borrador*/
int color_click(int x, int y)
{
    if (x >= 103 && x <= 151 && y >= 23 && y <= 45)
        return RED;

    if (x >= 155 && x <= 203 && y >= 23 && y <= 45)
        return YELLOW;

    if (x >= 207 && x <= 255 && y >= 23 && y <= 45)
        return GREEN;

    if (x >= 259 && x <= 307 && y >= 23 && y <= 45)
        return MAGENTA;

    if (x >= 311 && x <= 359 && y >= 23 && y <= 45)
        return BLUE;

    if (x >= 363 && x <= 411 && y >= 23 && y <= 45)
        return BLACK;

     if (x >= 502 && x <= 553 && y >= 24 && y <= 70)
        return WHITE;

    return -1;
}

/*boton salir*/
int salir_click(int x, int y)
{

    if (x >= 564 && x <= 615 && y >= 24 && y <= 70)
        return 99;
    return -1;
}

/*diesño y logica paint*/
void all_funtion()
{
    int mouse_x, mouse_y, button;
    int prev_x = -1, prev_y = -1;
    int figure_code, color_code;
    int running = 1;

    int tablacolores[] = {96, 19, 96, 75, 622, 75, 622, 19, 96, 19};
    int rojo[] = {103, 23, 151, 23, 151, 45, 103, 45, 103, 23};
    int amarillo[] = {155, 23, 203, 23, 203, 45, 155, 45, 155, 23};
    int verde[] = {207, 23, 255, 23, 255, 45, 207, 45, 207, 23};
    int magenta[] = {259, 23, 307, 23, 307, 45, 259, 45, 259, 23};
    int azul[] = {311, 23, 359, 23, 359, 45, 311, 45, 311, 23};
    int negro[] = {363, 23, 411, 23, 411, 45, 363, 45, 363, 23};

    int cuadroborrador[] = {502, 24, 553, 24, 553, 70, 502, 70, 502, 24};
    int borrador[] = {510, 55, 531, 34, 543, 46, 526, 63, 518, 63, 510, 55};
    int cuadrosalir[] = {564, 24, 615, 24, 615, 70, 564, 70, 564, 24};
    int cuadrocirculo[] = {8, 95, 87, 95, 87, 166, 8, 166, 8, 95};
    int cuadrocuadrado[] = {9, 196, 88, 196, 88, 267, 9, 267, 9, 196};
    int cuadrotriangulo[] = {8, 297, 87, 297, 87, 368, 8, 368, 8, 297};
    int cuadrolinea[] = {8, 397, 87, 397, 87, 468, 8, 468, 8, 397};
    int tableroprincipal[] = {0, 0, 639, 0, 639, 96, 95, 96, 95, 479, 0, 479, 0, 0};
    int cua[] = {25, 212, 72, 212, 72, 252, 25, 252, 25, 212};
    int tria[] = {23, 355, 47, 311, 72, 355, 23, 355};
    int lie[] = {46, 404, 48, 404, 48, 461, 46, 461, 46, 404};
    int sali[] = {571, 32, 608, 32, 608, 62, 571, 62, 571, 56, 599, 56, 599, 38, 571, 38, 571, 32};
    int flecha9[] = {571, 45, 581, 45, 581, 49, 571, 49, 571, 45};
    int pantalla5[] = {96, 97, 639, 97, 639, 479, 96, 479, 96, 97};
    int flecha8[] = {583, 43, 587, 47, 587, 48, 583, 51, 583, 43};

    cleardevice();
    srand(time(NULL));

    setcolor(BLUE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    fillpoly(7, tableroprincipal);
    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);
    fillpoly(5, tablacolores);
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    fillpoly(5, rojo);
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillpoly(5, amarillo);
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    fillpoly(5, verde);
    setcolor(MAGENTA);
    setfillstyle(SOLID_FILL, MAGENTA);
    fillpoly(5, magenta);
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    fillpoly(5, azul);
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillpoly(5, negro);   
    setcolor(LIGHTGRAY);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    fillpoly(5, cuadroborrador);
    fillpoly(5, cuadrosalir);
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillpoly(6, borrador);
    fillpoly(5, pantalla5);
    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);
    fillpoly(5, cuadrocirculo);
    fillpoly(5, cuadrocuadrado);
    fillpoly(5, cuadrotriangulo);
    fillpoly(5, cuadrolinea);
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillpoly(5, cua);
    fillpoly(4, tria);
    fillpoly(5, lie);
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillpoly(9, sali);
    fillpoly(5, flecha9);
    fillpoly(5, flecha8);
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(47, 130, 27, 27);

    if (!mouse_init())
    {
        closegraph();
        printf("Mouse no detectado.\n");
        getch();
        return;
    }

    move_mouse(0, 483);
    showe_mouse();

    while (running)
    {
        get_mouse_status(&button, &mouse_x, &mouse_y);

        color_code = color_click(mouse_x, mouse_y);
        if (color_code != -1)
        {
            current_color = color_code;
            prev_x = prev_y = -1;
        }

        figure_code = salir_click(mouse_x, mouse_y);
        if (figure_code != -1)
        {
            if (figure_code == 99 && (button & 1))
                running = 0;
            prev_x = prev_y = -1;
        }

        if (mouse_x >= AREA_X1 && mouse_x <= AREA_X2 && mouse_y >= AREA_Y1 && mouse_y <= AREA_Y2 && (button & 1))
        {
            setcolor(current_color);
            if (prev_x != -1)
                line(prev_x, prev_y, mouse_x, mouse_y);
            else
                putpixel(mouse_x, mouse_y, current_color);
            prev_x = mouse_x;
            prev_y = mouse_y;
        }
        else
        {
            prev_x = prev_y = -1;
        }

        if (kbhit() && getch() == 27)
            running = 0;
        delay(1);
    }

    hide_mouse();
    return;
}

/*funcion principal*/
void funcion_paint() {
	all_funtion();
}

#endif
