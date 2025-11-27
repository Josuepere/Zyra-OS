#ifndef ESTRELLAS_H
#define ESTRELLAS_H

/*librias necesarias*/
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <time.h>

#define NEGRO 0
#define BLANCO 15
#define GRIS_CLARO 7
#define AZUL_CIAN 3
#define ROJO_CLARO 4

/*prototipos*/
void dibujar_estrellas(int num_estrellas);
void fondo_estrellas();

/*funcion dibujar estrellas, simulacion de galaxia*/
void dibujar_estrellas(int num_estrellas) {
    int x_max = getmaxx();
    int y_max = getmaxy();
    int i, x, y, color;


    for (i = 0; i < num_estrellas; i++) {

        x = rand() % x_max;
        y = rand() % y_max;


        if (rand() % 2 == 0) {
	    color = i % 2 == 0 ? BLANCO : AZUL_CIAN;
        } else {
            color = i % 2 != 0 ? GRIS_CLARO : ROJO_CLARO;
        }

	putpixel(x,y,color);
	}
}

/*funcion de animacion*/
void fondo_estrellas() {
    int x_center, y_center;
    int num_estrellas = 400;

    srand(time(NULL));

    while (1) {

        cleardevice();
        dibujar_estrellas(num_estrellas);
	delay(1500);

        if (kbhit()) {
		int o = getch();
		if (o == 49) {
			 break;
		}
        }
    }
    return;
}

#endif