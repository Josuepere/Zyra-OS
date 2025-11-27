#ifndef OPCIONES_H
#define OPCIONES_H

/*librerias necesarias*/
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include<girasol3.h>
#include<fondo.h>
#include<fondobur.h>

union REGS in, out;
int fondo_establecido = 0;
int suspensop = 0;

/*prototipos*/
void protector();
void iniciarc_mouse();
void mostrarc_mouse();
void oculc_mouse();
void obtenerc_pocision_mouse(int *x, int *y, int *click);
void fondo_dibujar();
void cuadro_texto9();

/*logica detras de configuraciones*/
void fondo_dibujar(){
	if (fondo_establecido == 1) {
		fondopantalla4();
	} else if (fondo_establecido == 2) {
		fondopantalla2();
		return 1;
	} else if (fondo_establecido == 3) {
		fondopantalla3();
	} else if (fondo_establecido == 4) {
		fondopantalla1();
	} else {
		fondopantalla4();
	}
}

/*logica detras de salvapantallas*/
void suspeno() {
	if (suspensop == 1){
		fondo_estrellas();
	} else if (suspensop == 2) {
		fondo_burbujas();
	} else {
		fondo_burbujas();
	}
}

/*Mensaje de confirmacion*/
void cuadro_texto9() {
	int cuadro1[] = {165, 190, 165, 289, 484, 289, 484, 190, 165, 190};
	int cuadro2[] = {169, 194, 169, 285, 480, 285, 480, 194, 169, 194};

	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	fillpoly(4, cuadro1);
	setfillstyle(SOLID_FILL, WHITE);
	fillpoly(4, cuadro2);
}

/*protector de pantalla*/
void protector(){

	int fon[]={56,65,56,140,177,140,177,65,56,65};
	int fon1[]={56,141,56,155,177,155,177,141,56,141};
	int col[]={102,156,102,166,131,166,131,156,102,156};
	int bas[]={67,167,67,173,166,173,166,167,67,167};
	int estrella[]={79,76,79,82,85,82,85,76,79,76};
	int estre1[]={68,111,68,117,74,117,74,111,68,111};
	int estre2[]={79,122,79,128,85,128,85,122,79,122};
	int estre3[]={148,122,148,128,154,128,154,122,148,122};
	int estre4[]={159,88,159,94,165,94,165,88,159,88};
	int estre5[]={148,76,154,76,154,82,148,82,148,76};
	int fond[]={62,324,181,324,181,247,62,247,62,324};
	int fond1[]={69,254,69,317,174,317,174,254,69,254};
	int fond2[]={76,261,76,310,152,310,152,261,76,261};
	int montanas[]={76,291,93,273,110,292,122,279,136,295,142,289,
					152,300,152,310,76,310,76,291};
	int cd[]={161,261,161,267,167,267,167,261,161,261};
	int cd1[]={161,275,167,275,167,281,161,281,161,275};
	int cd2[]={161,289,167,289,167,295,161,295,161,289};
	int cd3[]={161,304,161,309,167,309,167,304,161,304};
	int cd4[]={105,324,135,324,135,338,105,338,105,324};
	int cd5[]={62,338,181,338,181,343,62,343,62,338};
	int recd1[]={281,83,281,123,399,123,399,83,281,83};
	int recd2[]={286,88,286,118,394,118,394,88,286,88};
	int recd3[]={280,144,280,182,400,182,400,144,280,144};
	int recd4[]={285,149,285,177,395,177,395,149,285,149};
	int recd5[]={429,83,429,123,548,123,548,83,429,83};
	int recd6[]={434,88,434,118,543,118,543,88,434,88};
	int recd7[]={280,268,280,306,400,306,400,268,280,268};
	int recd8[]={285,273,285,301,395,301,395,273,285,273};
	int recd9[]={279,317,279,353,400,353,400,317,279,317};
	int recd10[]={284,322,284,348,395,348,395,322,284,322};
	int recd11[]={280,362,280,399,400,399,400,362,280,362};
	int recd12[]={285,367,285,394,395,394,395,367,285,367};
	int recd13[]={279,409,279,445,402,445,402,409,279,409};
	int recd14[]={284,414,284,440,397,440,397,414,284,414};

	setcolor(DARKGRAY);
	setfillstyle(SOLID_FILL,DARKGRAY);
	fillpoly(5,fon);
	fillpoly(5,col);

	setcolor(CYAN);
	setfillstyle(SOLID_FILL,CYAN);
	fillpoly(5,fon1);
	fillpoly(5,bas);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,WHITE);
	circle(117,105,25);
	floodfill(117,105,WHITE);

	setcolor(DARKGRAY);
	setfillstyle(SOLID_FILL,DARKGRAY);
	fillpoly(5,fond);
	fillpoly(5,cd5);
	circle(91,103,25);
	floodfill(91,103,DARKGRAY);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,WHITE);
	fillpoly(5,estrella);
	fillpoly(5,estre1);
	fillpoly(5,estre2);
	fillpoly(5,estre3);
	fillpoly(5,estre4);
	fillpoly(5,estre5);
	fillpoly(5,fond1);

	setcolor(CYAN);
	setfillstyle(SOLID_FILL,CYAN);
	fillpoly(5,fond2);
	fillpoly(5,cd4);

	setcolor(GREEN);
	setfillstyle(SOLID_FILL,GREEN);
	fillpoly(10,montanas);

	setcolor(BLUE);
	setfillstyle(SOLID_FILL,BLUE);
	fillpoly(5,recd1);
	fillpoly(5,recd3);
	fillpoly(5,recd5);
	fillpoly(5,recd7);
	fillpoly(5,recd9);
	fillpoly(5,recd11);
	fillpoly(5,recd13);

	setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	fillpoly(5,cd);
	fillpoly(5,cd1);
	fillpoly(5,cd2);
	fillpoly(5,cd3);

	setcolor(DARKGRAY);
	setfillstyle(SOLID_FILL,DARKGRAY);
	fillpoly(5,recd2);
	fillpoly(5,recd4);
	fillpoly(5,recd6);
	fillpoly(5,recd8);
	fillpoly(5,recd10);
	fillpoly(5,recd12);
	fillpoly(5,recd14);

	setcolor(WHITE);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
	outtextxy(260,30,"Protectores de pantalla:");
	outtextxy(280,210,"Fondos de pantalla:");

	settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
	outtextxy(300,90,"Opcion 1");
	outtextxy(300,150,"Opcion 2");
	outtextxy(450,90,"Opcion 3");
	outtextxy(290,275,"Por defecto");
	outtextxy(300,323,"Opcion 1");
	outtextxy(300,368,"Opcion 2");
	outtextxy(300,415,"Opcion 3");

	setfillstyle(SOLID_FILL, RED);
    	bar(600, 10, 630, 35);
    	setcolor(WHITE);
    	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	outtextxy(609, 15, "<");
}

/*funciones mouse*/
void iniciarc_mouse(){
	in.x.ax = 0;
	int86(0x33, &in, &out);
}

void mostrarc_mouse(){
	in.x.ax = 1;
	int86(0x33, &in, &out);
}

void obtenerc_pocision_mouse(int *x, int *y, int *click){
	in.x.ax = 3;
	int86(0x33, &in, &out);
	*click = out.x.bx;
	*x = out.x.cx;
	*y = out.x.dx;

}

void oculc_mouse()
{
	in.x.ax = 2;
	int86(0x33, &in, &out);
}

void moverc_mouse(int x, int y){
	in.x.ax = 4;
	in.x.cx = x;
	in.x.dx = y;
	int86(0x33, &in, &out);
}

void accionc_mouse(){
	int mx, my, click, correcto;

	iniciarc_mouse();
	mostrarc_mouse();

	/*logica de clicks*/
	while(1) {
		obtenerc_pocision_mouse(&mx, &my, &click);
		if (click == 1){
			if (mx >= 280 && mx <= 400 && my >= 268 && my <= 306){
				oculc_mouse();
				cleardevice();
				fondo_establecido = 1;
				fondopantalla4();
				cuadro_texto9();
				outtextxy(190, 236, "Fondo Establecido");
				delay(1700);
				cleardevice();
				protector();
				mostrarc_mouse();
			}
			if (mx >= 279 && mx <= 400 && my >= 317 && my <= 353){
				oculc_mouse();
				cleardevice();
				fondo_establecido = 2;
				fondopantalla2();
				cuadro_texto9();
				outtextxy(190, 236, "Fondo Establecido");
				delay(1700);
				cleardevice();
				protector();
				mostrarc_mouse();
			}
			if (mx >= 280 && mx <= 400 && my >= 362 && my <= 399) {
				oculc_mouse();
				cleardevice();
				fondo_establecido = 3;
				fondopantalla3();
				cuadro_texto9();
				outtextxy(190, 236, "Fondo Establecido");
				delay(1700);
				cleardevice();
				protector();
				mostrarc_mouse();
			}
			if (mx >= 279 && mx <= 402 && my >= 409 && my <= 445) {
				oculc_mouse();
				cleardevice();
				fondo_establecido = 4;
				fondopantalla1();
				cuadro_texto9();
				outtextxy(190, 236, "Fondo Establecido");
				delay(1700);
				cleardevice();
				protector();
				mostrarc_mouse();
			}
			if (mx >= 281 && mx <= 399 && my >= 83 && my <= 123) {
				oculc_mouse();
				suspensop = 1;
				cleardevice();
				cuadro_texto9();
				outtextxy(230, 236, "Establecido");
				delay(1700);
				cleardevice();
				protector();
				mostrarc_mouse();
			}
			if (mx >= 280 && mx <= 400 && my >= 144 && my <= 182) {
				oculc_mouse();
				suspensop = 2;
				cleardevice();
				cuadro_texto9();
				outtextxy(230, 236, "Establecido");
				delay(1700);
				cleardevice();
				protector();
				mostrarc_mouse();
			}
			if (mx >= 600 && mx <= 630 && my >= 10 && my <= 35) {
				oculc_mouse();
				cleardevice();
				return;
			}
		}
		delay(10);
	}

	return;
}

/*funcion principal*/
void funcion_opciones() {
	cleardevice();
	protector();
	delay(200);
	accionc_mouse();

	return;

}

#endif