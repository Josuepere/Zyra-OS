#ifndef MOUSE_H
#define MOUSE_H
/*libreria necesarias*/
#include <dos.h>

union REGS in, out;

/*prototipos*/
void iniciar_raton();
void mostrar_raton();
void ocultar_raton();
void obtener_posicion_raton(int *x, int *y, int *click);
void mover_raton(int x, int y);

/*funciones mouse*/
void iniciar_raton() {
    in.x.ax = 0;
    int86(0x33, &in, &out);
}

void mostrar_raton() {
    in.x.ax = 1;
    int86(0x33, &in, &out);
}

void ocultar_raton() {
    in.x.ax = 2;
    int86(0x33, &in, &out);
}

void obtener_posicion_raton(int *x, int *y, int *click) {
    in.x.ax = 3;
    int86(0x33, &in, &out);

    *click = out.x.bx; 
    *x = out.x.cx;
    *y = out.x.dx;
}

void mover_raton(int x, int y){
    in.x.ax = 4;
    in.x.cx = x;
    in.x.dx = y;
    int86(0x33, &in, &out);
}

#endif