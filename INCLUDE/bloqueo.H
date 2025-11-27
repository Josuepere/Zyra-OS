#ifndef BLOQUEO_H
#define BLOQUEO_H

/*librerias necesarias*/
#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <inicio.h>
#include <cargalo.h>
#include <descarga.h>

union REGS iy, ou;
char contra[18] = "";

/*prototipos*/
void fondo_bloqueo();
void iniciar_mouse();
void mos_mouse();
void obtener_pocision_mouse(int *x, int *y, int *click);
void boton_apagado();
void icono_usuario();
void dibujar_input(char *entrada, int focus);
int accion_boton_input(char *cadena, int tamanio_cadena);
void mover_mouse(int x, int y);
void accion_mouse();
void funcion_bloqueo();

/*fondo interfaz de bloqueo*/
void fondo_bloqueo() {
	int triangulo1[] = {461, 335, 194, 479, 237, 479, 441, 368, 438, 479, 461, 479, 461, 335};
	int triangulo2[] = {501, 274, 114, 479, 156, 479, 481, 304, 481, 479, 501, 479, 501, 274};
	int triangulo3[] = {581, 365, 565, 479, 588, 479, 597, 402, 639, 434, 639, 408, 581, 365};
	int triangulo4[] = {555, 302, 532, 479, 553, 479, 570, 337, 639, 390, 639, 365, 555, 302};
	int triangulo5[] = {546, 279, 519, 479, 524, 479, 549, 285, 639, 354, 639, 350, 546, 279};
	int triangulo6[] = {566, 231, 639, 274, 639, 250, 607, 231, 639, 213, 639, 188, 566, 231};
	int triangulo7[] = {328, 47, 352, 0, 375, 0, 362, 24, 496, 18, 484, 0, 509, 0, 534, 38, 328, 47};
	int triangulo8[] = {309, 0, 262, 88, 602, 73, 556, 0, 532, 0, 568, 55, 297, 68, 332, 0, 309, 0};
	int triangulo9[] = {299, 0, 246, 103, 628, 86, 572, 0, 568, 0, 621, 82, 251, 100, 303, 0, 299, 0};
	int triangulo10[] = {0, 285, 141, 367, 0, 448, 0, 424, 100, 366, 0, 308, 0, 285};
	int triangulo11[] = {0, 238, 222, 366, 28, 479, 0, 479, 0, 472, 182, 366, 0, 260, 0, 238};
	int triangulo12[] = {249, 365, 52, 479, 47, 479, 241, 365, 0, 226, 0, 223, 249, 365};
	int triangulo13[] = {102, 203, 219, 0, 195, 0, 102, 162, 7, 0, 0, 0, 0, 29, 102, 203};
	int triangulo14[] = {102, 280, 263, 0, 239, 0, 102, 239, 0, 67, 0, 105, 102, 280};
	setbkcolor(BLUE);

	setcolor(3);
	setfillstyle(SOLID_FILL, 3);
	fillpoly(7, triangulo1);
	fillpoly(7, triangulo2);
	fillpoly(7, triangulo6);
	fillpoly(9, triangulo7);
	fillpoly(9, triangulo8);
	fillpoly(7, triangulo10);
	fillpoly(8, triangulo11);

	setcolor(YELLOW);
	setfillstyle(SOLID_FILL, YELLOW);
	fillpoly(7, triangulo3);
	fillpoly(7, triangulo4);
	fillpoly(7, triangulo13);
	fillpoly(7, triangulo14);

	setcolor(DARKGRAY);
	setfillstyle(SOLID_FILL, RED);
	fillellipse(264, 221, 93, 93);
	fillellipse(462, 160, 56, 56);
	setfillstyle(SOLID_FILL, BLUE);
	fillellipse(462, 160, 40, 40);
	fillellipse(264, 221, 73, 73);
	setfillstyle(SOLID_FILL, RED);
	fillellipse(462, 160, 26, 26);
	fillellipse(264, 221, 48, 48);
	setfillstyle(SOLID_FILL, BLUE);
	fillellipse(462, 160, 10, 10);
	fillellipse(264, 221, 28, 28);


	setcolor(DARKGRAY);
	setfillstyle(SOLID_FILL, DARKGRAY);
	fillpoly(7, triangulo5);
	fillpoly(9, triangulo9);
	fillpoly(7, triangulo12);
}

/*funciones del mouse*/
void iniciar_mouse(){
	iy.x.ax = 0;
	int86(0x33, &iy, &ou);
}

void mos_mouse(){
	iy.x.ax = 1;
	int86(0x33, &iy, &ou);
}

void obtener_pocision_mouse(int *x, int *y, int *click){
	iy.x.ax = 3;
	int86(0x33, &iy, &ou);
	*click = ou.x.bx;
	*x = ou.x.cx;
	*y = ou.x.dx;

}

/*boton de apagado */
void boton_apagado(){
	setcolor(DARKGRAY);
	setfillstyle(SOLID_FILL, WHITE);
	fillellipse(602, 446, 18, 18);
	setfillstyle(SOLID_FILL, BLUE);
	fillellipse(602, 446, 14, 14);
	setfillstyle(SOLID_FILL, WHITE);
	fillellipse(602, 436, 3, 10);
}

/*icono de usuario diseño*/
void icono_usuario(){
	int cuerpo[] = {286, 188, 291, 157, 292, 157, 292, 156, 293, 156, 293, 154, 294, 154, 294, 153,
					295, 153, 295, 152, 296, 152, 296, 151, 297, 150, 298, 149, 299, 149, 300, 148,
					302, 148, 304, 147, 348, 147, 349, 148, 351, 148, 352, 149, 353, 150, 354, 150,
					355, 151, 356, 152, 357, 153, 358, 154, 359, 155, 360, 156, 365, 188, 357, 193,
					354, 162, 348, 154, 303, 154, 297, 162, 294, 193, 286, 188};

	int puntos = sizeof(cuerpo) / (2 * sizeof(int));

	setcolor(DARKGRAY);
	setfillstyle(SOLID_FILL, WHITE);
	fillellipse(326, 136, 69, 69);
	setfillstyle(SOLID_FILL, BLUE);
	fillellipse(326, 136, 62, 62);
	setfillstyle(SOLID_FILL, WHITE);
	fillellipse(326, 122, 25, 25);
	setfillstyle(SOLID_FILL, BLUE);
	fillellipse(326, 122, 18, 18);

	setfillstyle(SOLID_FILL, WHITE);
	fillpoly(puntos, cuerpo);

	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
	setcolor(WHITE);
	outtextxy(180, 210, "Derek Josue Perez Gonzalez");
}

/*diseño del input contraseña*/
void dibujar_input(char *entrada, int focus){
	int coordenada_input[] = {202, 268+10, 202, 304+10, 437, 304+10, 437, 268+10, 202, 268+10};
	int coordenada_input2[] = {203, 269+10, 203, 303+10, 436, 303+10, 436, 269+10, 203, 269+10};

	setcolor(focus ? YELLOW : WHITE);
	fillpoly(5, coordenada_input);
	setfillstyle(SOLID_FILL, WHITE);
	fillpoly(5, coordenada_input2);
	setcolor(DARKGRAY);
	outtextxy(204, 270+10, entrada);
}

/*logica del input, comprobacion de la contraseña*/
int accion_boton_input(char *cadena, int tamanio_cadena){
    int coordenada_input2[] = {203, 279, 203, 313, 436, 313, 436, 279, 203, 279};
    int i, blink, textx, texty;
    char caracter_escritorio;

    i = strlen(cadena);
    blink = 0;

    while (1)
    {
        setfillstyle(SOLID_FILL, WHITE);
        fillpoly(5, coordenada_input2);
        setcolor(DARKGRAY);
        outtextxy(204, 280, cadena);

        textx = 204 + textwidth(cadena);
        texty = 285;

        if (blink){
			line(textx, texty, textx, texty + textheight("A"));
		}

        delay(300);
        blink = !blink;

        if (kbhit()){
            caracter_escritorio = getch();

			if (caracter_escritorio == 13) {
				if (strcmp(cadena, "1234") == 0) {
		    			cadena[0] = '\0';
                    			i = 0;
					return 1;
				} else {
		    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    setcolor(RED);
                    outtextxy(250, 320, "Incorrect Password");
                    delay(1000);
                    setcolor(BLUE);
                    outtextxy(250, 320, "Incorrect Password");
		    cadena[0] = '\0';
                    i = 0;
		    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
		    return 0;
                }
            }
            else if (caracter_escritorio == 8 && i > 0)
            {
                i--;
                cadena[i] = '\0';
            }
            else if (caracter_escritorio >= 32 && caracter_escritorio <= 126 && i < tamanio_cadena - 1)
            {
                cadena[i] = caracter_escritorio;
                i++;
                cadena[i] = '\0';
            }
        }
    }
    return 0;
}

/*funciones mouse*/
void mover_mouse(int x, int y){
	iy.x.ax = 4;
	iy.x.cx = x;
	iy.x.dx = y;
	int86(0x33, &iy, &ou);
}

void accion_mouse(){
	int mx, my, click, correcto;

	setcolor(WHITE);
	outtextxy(260, 240+6, "Password: ");
	dibujar_input(contra, 0);
	iniciar_mouse();
	mos_mouse();


	while(1) {
		obtener_pocision_mouse(&mx, &my, &click);
		if (click == 1){
			if (mx >= 584 && mx <= 620 && my >= 428 && my <= 464) {
				delay(200);
				cleardevice();
				setbkcolor(BLACK);
				apagado_carga();
				delay(100);
				closegraph();
				exit(0);
			}
			if (mx >= 202 && mx <= 437 && my >= 268+10 && my <= 304+10){
				dibujar_input(contra, 1);
				correcto = accion_boton_input(contra, 17);
				mover_mouse(650, 483);
				if (correcto == 1){
					dibujar_input(contra, 0);
					cleardevice();
					setbkcolor(BLACK);
					animacion_carga();
					delay(100);
					cleardevice();
					setbkcolor(BLACK);
					funcion_inicio();
					cleardevice();
					fondo_bloqueo();
					icono_usuario();
					boton_apagado();
					setcolor(WHITE);
					outtextxy(260, 240+6, "Password: ");
					dibujar_input(contra, 0);
					mos_mouse();
				} else {
					dibujar_input(contra, 0);
				}
			} else {
				dibujar_input(contra, 0);
			}
		}
		delay(50);
	}
}

/*funcion principal*/
void funcion_bloqueo(){
	cleardevice();

	fondo_bloqueo();
	icono_usuario();
	boton_apagado();
	accion_mouse();
}

#endif