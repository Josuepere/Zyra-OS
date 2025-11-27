#ifndef AJUSTE_H
#define AJUSTE_H

/*librerias necesarias*/
#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include<graphics.h>
#include <opciones.h>
#include <descarga.h>

union REGS in, out;

/*prototipos*/
void inicioset();
void iniciarf_mouse();
void mostrarf_mouse();
void obtenerf_posicion_mouse(int *x, int *y, int *click);
void oculf_mouse();
void accionf_mouse();
void moverf_mouse(int x, int y);
void icono_sus();
void boton_apagado2();

/*funcion opciones: muestra la interfaz de opciones*/
void funcion_opcionesoo(){
	cleardevice();

	inicioset();
	delay(300);
	accionf_mouse();
}

/*funcion boton apagado*/
void boton_apagado2(){
	setcolor(DARKGRAY);
	setfillstyle(SOLID_FILL, WHITE);
	fillellipse(602, 446, 18, 18);
	setfillstyle(SOLID_FILL, BLACK);
	fillellipse(602, 446, 14, 14);
	setfillstyle(SOLID_FILL, WHITE);
	fillellipse(602, 436, 3, 10);
}

void icono_sus() {
	int circulo1[] = {470, 449, 470, 447, 471, 444, 472, 443, 474, 441, 474, 440,
						475, 439, 476, 439, 478, 437, 479, 437, 480, 436,
						550, 436, 551, 437, 552, 437, 558, 443, 558, 444, 559,
						445, 559, 452, 558, 453, 558, 455, 557, 456, 557, 457,
						554, 460, 553, 460, 551, 462, 549, 462, 548, 463, 480,
						463, 479, 462, 478, 463, 476, 460, 475, 460, 472, 457,
						472, 456, 471, 455, 471, 453, 470, 452, 470, 449};

	int puntos22 = sizeof(circulo1) / (2 * sizeof(int));

	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	fillpoly(puntos22, circulo1);
	setcolor(BLACK);
	outtextxy(479, 447, "SUSPENDER");

}

/*interfaz de configuraciones*/
void inicioset(){

	int cuerpo[]={95,168,109,130,175,130,195,169};

	int boton[]={69,217,69,314,464,314,464,217,69,217};

	int boton1[]={459,222,459,309,74,309,74,222,459,222};

	int compu[]={79,229,79,281,168,281,168,229,79,229};

	int recuadro[]={79,281,79,290,168,290,168,281,79,281};

	int borde[]={83,232,83,277,164,277,164,232,83,232};

	int base[]={113,291,110,304,136,304,133,291,113,291};

	int botonc[]={123,284,124,284,124,286,123,286,123,284};

	int detalle[]={90,239,121,239,121,256,90,256,90,239};

	int linea[]={90,261,121,261};

	int linea1[]={90,265,121,265};

	int linea2[]={90,269,121,269};

	int linea3[]={90,273,121,273};

	int detalle1[]={129,239,129,243,134,243,134,239,129,239};

	int detalle2[]={129,249,129,253,134,253,134,249,129,249};

	int detalle3[]={129,259,129,263,134,263,134,259,129,259};

	int detalle4[]={129,269,129,273,134,273,134,269,129,269};

	int punta[]={145,264,146,265,152,265,156,262,156,258,155,257,150,258,

				148,261,145,264};

	int pincel[]={155,257,160,248,165,251,156,258,155,257};

	int pincel1[]={160,248,179,224,182,223,185,226,185,231,165,250,160,248};

	int linea4[]={140,239,156,239};

	int linea5[]={140,243,156,243};

	int linea6[]={140,249,156,249};

	int linea7[]={140,253,153,253};

	int linea8[]={140,259,144,259};

	int linea9[]={140,263,141,263};

	int linea10[]={140,269,156,269};

	int linea11[]={140,273,156,273};

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,DARKGRAY);
	circle(145,110,80);
	floodfill(145,110,WHITE);


	setcolor(WHITE);
	circle(145,90,31);
	drawpoly(4,cuerpo);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,WHITE);
	fillpoly(5,boton);

	setcolor(BLUE);
	setfillstyle(SOLID_FILL,BLUE);
	fillpoly(5,boton1);

	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	fillpoly(5,compu);
	fillpoly(5,base);

	setcolor(BLACK);
	setfillstyle(SOLID_FILL,WHITE);
	fillpoly(5,recuadro);


	setcolor(CYAN);
	setfillstyle(SOLID_FILL,CYAN);
	fillpoly(5,borde);

	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	fillpoly(5,botonc);

	setcolor(BLACK);
	drawpoly(5,detalle);
	drawpoly(2,linea);
	drawpoly(2,linea1);
	drawpoly(2,linea2);
	drawpoly(2,linea3);
	drawpoly(2,linea4);
	drawpoly(2,linea5);
	drawpoly(2,linea6);
	drawpoly(2,linea7);
	drawpoly(2,linea8);
	drawpoly(2,linea9);
	drawpoly(2,linea10);
	drawpoly(2,linea11);
	setfillstyle(SOLID_FILL,BLACK);
	fillpoly(5,detalle1);
	fillpoly(5,detalle2);
	fillpoly(5,detalle3);
	fillpoly(5,detalle4);
	fillpoly(5,pincel);

	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BROWN);
	fillpoly(9,punta);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,WHITE);
	fillpoly(7,pincel1);

	setcolor(WHITE);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
	outtextxy(210,250,"Personalizacion");
	outtextxy(260,54,"Derek Perez");

	setcolor(WHITE);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
	outtextxy(262,94,"derek.perez196@std.uni.edu.ni");

    setfillstyle(SOLID_FILL, RED);
    bar(600, 10, 630, 35);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(608, 15, "X");

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	icono_sus();
	boton_apagado2();
}

/*funciones mouse*/
void iniciarf_mouse(){
	in.x.ax = 0;
	int86(0x33, &in, &out);
}

void mostrarf_mouse(){
	in.x.ax = 1;
	int86(0x33, &in, &out);
}

void obtenerf_pocision_mouse(int *x, int *y, int *click){
	in.x.ax = 3;
	int86(0x33, &in, &out);
	*click = out.x.bx;
	*x = out.x.cx;
	*y = out.x.dx;

}

void oculf_mouse()
{
	in.x.ax = 2;
	int86(0x33, &in, &out);
}

void moverf_mouse(int x, int y){
	in.x.ax = 4;
	in.x.cx = x;
	in.x.dx = y;
	int86(0x33, &in, &out);
}

/*logica de click detras de configuraciones*/
void accionf_mouse(){
	int mx, my, click, correcto;

	iniciarf_mouse();
	mostrarf_mouse();


	while(1) {
		obtenerf_pocision_mouse(&mx, &my, &click);
		if (click == 1){
			if (mx >= 69 && mx <= 464 && my >= 217 && my <= 314){
				moverf_mouse(0, 645);
				oculf_mouse();
				cleardevice();
				funcion_opciones();
				cleardevice();
				inicioset();
				delay(300);
				mostrarf_mouse();
			}
			if (mx >= 584 && mx <= 620 && my >= 428 && my <= 464) {
				delay(200);
				cleardevice();
				setbkcolor(BLACK);
				apagado_carga();
				delay(100);
				closegraph();
				exit(0);
			}
			if (mx >= 470 && mx <= 559 && my >= 436 && my <= 463){
				oculf_mouse();
				cleardevice();
				suspeno();
				cleardevice();
				inicioset();
				delay(300);
				mostrarf_mouse();
			}
			if (mx >= 600 && mx <= 630 && my >= 10 && my <= 35) {
				oculf_mouse();
				cleardevice();
				return;
			}
		}
		delay(50);
	}
	return;
}

#endif