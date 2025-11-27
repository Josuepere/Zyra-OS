#ifndef BUR_H
#define BUR_H

/*librerias necesarias*/
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <time.h>

#define NEGRO        0
#define BLANCO       15
#define GRIS_CLARO   7
#define AZUL_CIAN    3
#define ROJO_CLARO   4

/*prototipos*/
void dibujarburb(int num_burb);
void fondo_burbujas();

/*funcion dibujar burbujas, salvapantallas*/
void dibujarburb(int num_burb) {
    int x_max = getmaxx();
    int y_max = getmaxy();
    int i, x, y, color;

    for (i = 0; i < num_burb; i++) {

        x = rand() % x_max;
        y = rand() % y_max;

        if (rand() % 2 == 0) {
            color = i % 2 == 0 ? AZUL_CIAN : ROJO_CLARO;
        } else {
            color = i % 2 != 0 ? BLANCO : GRIS_CLARO;
        }

        setcolor(color);
        circle(x, y, 20);
        delay(15);
    }
}

/*funcion principal*/
void fondo_burbujas() {
    int num_burb = 100;

    srand(time(NULL));

    while (1) {
        cleardevice();
        dibujarburb(num_burb);
        delay(500);

        if (kbhit()) {
		int o = getch();
		if (o == 50) {
			 break;
		}
        }
    }
    return;
}

#endif
