#ifndef INICIO_H
#define INICIO_H

/*librerias necesarias*/
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<time.h>
#include<mouse.h>
#include<calcula.h>
#include<ZyraDB.h>
#include<paint.h>
#include<blocnot.h>
#include<descarga.h>
#include<game.h>
#include<ajuste.h>
#include<opciones.h>

char hora[10];

int detallehora2[] = {544,452,619,452,619,466,544,466,544,452};

char texto[30];

time_t ultimo_tiempo = 0;

struct date fecha;

/*prototipo*/
void iniciar_raton();
void mostrar_raton();
void ocultar_raton();
void obtener_posicion_raton(int *x, int *y, int *click);
void logo_fondo();
void icono_app();
void iconos();
void iconos_escri();
void funcion_inicio();

/*funcion logo, fondo predeterminado*/
void logo_fondo(){

	int zeta[]={228,167,281,133,288,146,281,184,306,169,316,179,264,214,
				262,214,254,204,266,159,237,180,228,167};

	int sombrazeta[]={228,167,228,216,236,227,237,227,254,214,254,252,
						262,263,264,263,316,226,316,179,264,214,262,214,
						254,204,266,159,237,180,228,167};

	int sombra2[]={288,146,281,184,288,180,288,146};

	int raya[]={237,180,237,227};

	int raya2[]={254,204,254,214};

	int raya3[]={263,214,263,263};

	int letrar[]={320,167,354,214,372,203,360,186,367,179,381,179,
					389,191,407,178,394,164,392,163,384,163,384,161,
					383,160,383,157,382,156,382,153,381,153,380,149,
					375,145,366,143,355,143,320,167};

	int fondoletra[]={347,167,359,158,366,159,369,163,353,175,
						352,175,347,167};

	int sombraletrar[]={320,167,320,216,354,262,356,262,371,252,
						371,227,382,227,389,239,392,239,406,227,
						406,179,389,191,381,179,367,179,360,186,
						372,203,354,214,320,167};

	int raya4[]={354,214,354,262};

	int raya5[]={371,204,371,252};

	int raya6[]={389,191,389,239};

	int cable[]={260,53,272,73,276,70,265,51,260,53};

	int cable2[]={234,68,256,99,283,111,285,107,260,96,238,65,234,68};

	int cable3[]={211,88,215,84,236,114,232,118,211,88};

	int cuadro[]={180,350,260,350,260,360,180,360,180,350};

	setcolor(WHITE);
	circle(315,183,140);
	setfillstyle(SOLID_FILL,BLUE);
	floodfill(315,183,WHITE);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,YELLOW);
	fillpoly(12,zeta);
	fillpoly(22,letrar);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,BLACK);
	fillpoly(16,sombrazeta);
	fillpoly(4,sombra2);
	fillpoly(7,fondoletra);
	fillpoly(18,sombraletrar);

	setcolor(WHITE);
	setfillstyle(SOLID_FILL,WHITE);
	circle(277,76,9);
	circle(292,112,9);
	circle(238,122,9);
	floodfill(238,122,WHITE);
	floodfill(292,112,WHITE);
	floodfill(277,76,WHITE);
	fillpoly(5,cable);
	fillpoly(7,cable2);
	fillpoly(5,cable3);

	setcolor(WHITE);
	drawpoly(2,raya);
	drawpoly(2,raya2);
	drawpoly(2,raya3);
	drawpoly(2,raya4);
	drawpoly(2,raya5);
	drawpoly(2,raya6);
}

/*iconos barra de tareas*/
void icono_app() {
	int cuadro1[] = {29, 42, 47, 42, 47, 60, 29, 60, 29, 42};
	int cuadro2[] = {29, 23, 29, 41, 47, 41, 47, 23, 29, 23};
	int cuadro3[] = {48, 23, 48, 41, 67, 41, 67, 23, 48, 23};
	int cuadro4[] = {68, 23, 68, 41, 86, 41, 86, 23, 68, 23};
	int cuadro5[] = {48, 42, 67, 42, 67, 60, 48, 60, 48, 42};
	int cuadro6[] = {68, 42, 86, 42, 86, 60, 68, 60, 68, 42};
	int cuadro7[] = {68, 61, 68, 80, 86, 80, 86, 61, 68, 61};
	int cuadro8[] = {48, 61, 48, 80, 67, 80, 67, 61, 48, 61};
	int cuadro9[] = {29, 61, 29, 80, 47, 80, 47, 61, 29, 61};

	int curadro_externo1[] = {28, 79, 30, 81, 85, 81, 87, 79, 87, 24,
								85, 22, 30, 22, 28, 24, 28, 78, 29, 78,
								29, 24, 30, 24, 30, 23, 85, 23, 85, 24,
								86, 24, 86, 79, 85, 79, 85, 80, 30, 80,
								30, 79, 29, 79, 29, 78, 28, 79};

	int lines_internas[] = {28, 41, 87, 41, 87, 43, 28, 43, 28, 41};
	int lines_internas2[] = {26, 60, 87, 60, 87, 62, 28, 62, 28, 60};
	int lines_internas3[] = {47, 22, 47, 81, 48, 81, 48, 22, 47, 22};
	int lines_internas4[] = {67, 22, 67, 81, 68, 81, 68, 22, 67, 22};

	int x1[] = {73, 27, 82, 36, 82, 37, 80, 37, 72, 29, 72, 27, 73, 27};
	int x2[] = {82, 27, 82, 29, 74, 37, 72, 37, 72, 35, 80, 27, 82, 27};

	int x3[] = {52, 46, 54, 46, 63, 55, 63, 57, 61, 57, 52, 48, 52, 46};
	int x4[] = {63, 46, 63, 48, 54, 57, 52, 57, 52, 55, 61, 46, 63, 46};

	int x5[] = {44, 65, 44, 67, 36, 75, 34, 75, 34, 73, 42, 65, 44, 65};
	int x6[] = {34, 65, 36, 65, 44, 73, 44, 75, 42, 75, 34, 67, 34, 65};

	int puntos = sizeof(curadro_externo1) / (2 * sizeof(int));


	setcolor(BLACK);
	setfillstyle(SOLID_FILL, CYAN);
	fillpoly(5, cuadro1);
	fillpoly(5, cuadro2);
	fillpoly(5, cuadro3);
	fillpoly(5, cuadro6);
	fillpoly(5, cuadro7);
	fillpoly(5, cuadro8);
	setfillstyle(SOLID_FILL, WHITE);
	fillpoly(5, cuadro4);
	fillpoly(5, cuadro5);
	fillpoly(5, cuadro9);

	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	fillpoly(7, x1);
	fillpoly(7, x3);
	fillpoly(7, x5);
	line(74, 27, 82, 35);
	fillpoly(7, x2);
	fillpoly(7, x4);
	fillpoly(7, x6);

	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	fillellipse(58, 32, 6, 6);
	fillellipse(58, 70, 6, 6);
	setfillstyle(SOLID_FILL, WHITE);
	fillellipse(58, 32, 4, 4);
	fillellipse(58, 70, 4, 4);

	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	fillpoly(puntos, curadro_externo1);
	fillpoly(5, lines_internas);
	fillpoly(5, lines_internas2);
	fillpoly(5, lines_internas3);
	fillpoly(5, lines_internas4);
	line(30, 81, 85, 81);
	line(31, 21, 84, 21);	

}

/*barra de tareas*/
void iconos_escri() {
int tabla[] = {0,383,639,383,639,479,0,479,0,383};

int icono1[] = {12,392,103,392,103,472,12,472,12,392};

int icono2[] = {120,392,211,392,211,472,120,472,120,392};

int icono3[] = {328,392,419,392,419,472,328,472,328,392};

int icono4[] = {224,392,315,392,315,472,224,472,224,392};

int icono5[] = {432,392,523,392,523,472,432,472,432,392};


int sistema1[] = {60,420,51,411,33,411,24,420,24,458,26,460,89,460,92,457,92,423,89,420,24,420,60,420};

int paint1[] = {186,404,186,418,199,418,186,404,132,404,132,425,136,429,136,420,137,420,137,415,140,415,141,416,142,415,142,420,143,420,143,432,144,432,152,424,153,424,153,419,154,420,155,419,157,419,157,424,158,424,158,425,151,432,155,432,155,439,
151,439,151,463,199,463,199,418,186,404,132,404,186,404};

int detallepaint1[] = {151,439,132,439,132,463,151,463,151,439,155,439,155,432,128,432,128,439,151,439};

int detallepaint2[] = {138,431,132,425,129,428,133,431,138,431};

int detallepaint21[] = {131,425,128,427,126,425,129,425,129,420,125,420,125,425,129,425,129,423,131,425};

int detallepaint3[] = {143,431,143,423,136,423,136,429,138,431,143,431};

int detallepaint31[] = {143,423,136,423,136,420,142,420,142,415,141,416,140,415,137,415,137,420,143,420,143,423};

int detallepaint4[] = {145,431,150,426,157,426,152,431,145,431};

int detallepaint41[] = {157,426,151,426,151,425,156,424,157,424,157,419,155,419,154,420,153,419,153,424,158,424,158,425,157,425};

int nota[] = {407,460,407,415,400,408,400,460,340,460,340,408,343,408,343,412,348,412,348,408,355,408,355,412,360,412,360,408,367,408,367,412,372,412,372,408,379,408,379,412,384,412,384,408,391,408,391,412,396,412,396,408,400,408,400,460,407,460};

int detallenota1[] = {343,405,348,405,348,412,343,412,343,405};

int detallenota2[] = {355,405,360,405,360,412,355,412,355,405};

int detallenota3[] = {367,405,372,405,372,412,367,412,367,405};

int detallenota4[] = {379,405,384,405,384,412,379,412,379,405};

int detallenota5[] = {391,405,396,405,396,412,391,412,391,405};

int calculadora[] = {236,404,303,404,303,463,236,463,236,404};

int detallecal1[] = {244,412,296,412,296,424,244,424,244,412};

int detallecal2[] = {287,416,293,416,293,421,287,421,287,416};

int detallecal3[] = {244,431,253,431,253,438,244,438,244,431};

int detallecal4[] = {244,443,253,443,253,450,244,450,244,443};

int detallecal5[] = {244,454,253,454,253,461,244,461,244,454};

int detallecal6[] = {263,431,272,431,272,438,263,438,263,431};

int detallecal7[] = {263,443,272,443,272,450,263,450,263,443};

int detallecal8[] = {263,454,272,454,272,461,263,461,263,454};

int detallecal9[] = {283,431,292,431,292,438,283,438,283,431};

int detallecal10[] = {283,443,292,443,292,461,283,461,283,443};

int menu[] = {440,411,492,411,492,424,464,424,464,440,440,440,440,411};

int detallemenu1[] =  {440,403,492,403,492,411,440,411,440,403};

int detallemenu2[] = {464,431,513,431,513,459,464,459,464,431};

int detallemenu3[] = {464,424,513,424,513,431,464,431,464,424};

int detallemenu4[] = {470,406,474,406,474,409,470,409,470,406};

int detallemenu5[] = {478,406,482,406,482,409,478,409,478,406};

int detallemenu6[] = {485,406,489,406,489,409,485,409,485,406};

int detallemenu7[] = {493,426,497,426,497,429,493,429,493,426};

int detallemenu8[] = {500,426,504,426,504,429,500,429,500,426};

int detallemenu9[] = {507,426,511,426,511,429,507,429,507,426};

int detallemenu10[] = {446,416,460,416,460,427,446,427,446,416};

int detallemenu11[] = {471,436,485,436,485,447,471,447,471,436};

int detallemenu12[] = {466,419,487,419,466,419};

int detallemenu13[] = {462,425,463,425,462,425};

int detallemenu14[] = {446,430,463,430,446,430};

int detallemenu15[] = {446,435,455,435,446,435};

int detallemenu16[] = {458,435,460,435,458,435};

int detallemenu17[] = {489,439,507,439,489,439};

int detallemenu18[] = {489,443,498,443,489,443};

int detallemenu19[] = {502,443,507,443,502,443};

int detallemenu20[] = {489,447,507,447,489,447};

int detallemenu21[] = {471,451,497,451,471,451};

int detallemenu22[] = {501,451,507,451,501,451};

int detallemenu23[] = {471,455,507,455,471,455};

int detallefecha1[] = {548,400,616,400,616,411,548,411,548,400};

int detallefecha2[] = {544,416,619,416,619,430,544,430,544,416};

int detallehora1[] = {548,436,616,436,616,447,548,447,548,436};


int cuadro_tiempo[] = {536,392,627,392,627,472,536,472,536,392};

setcolor(LIGHTGRAY);
setfillstyle(SOLID_FILL,LIGHTGRAY);
fillpoly(5,tabla);


setcolor(BLUE);
setfillstyle(SOLID_FILL,BLUE);
fillpoly(5,icono1);
fillpoly(5,icono2);
fillpoly(5,icono3);
fillpoly(5,icono4);
fillpoly(5,icono5);



setcolor(LIGHTGRAY);
setfillstyle(SOLID_FILL,LIGHTGRAY);
fillpoly(5,calculadora);
fillpoly(5,detallemenu1);
fillpoly(5,detallemenu3);

setcolor(CYAN);
setfillstyle(SOLID_FILL,CYAN);
fillpoly(5,detallenota4);
fillpoly(5,detallenota3);
fillpoly(5,detallenota5);
fillpoly(5,detallenota1);
fillpoly(5,detallenota2);

setcolor(BLACK);
setfillstyle(SOLID_FILL,BLACK);
fillpoly(5,detallecal1);
fillpoly(5,cuadro_tiempo);

setcolor(LIGHTCYAN);
setfillstyle(SOLID_FILL,LIGHTCYAN);
fillpoly(10,detallepaint1);

setcolor(GREEN);
setfillstyle(SOLID_FILL,GREEN);
fillpoly(11,detallepaint31);

setcolor(YELLOW);
setfillstyle(SOLID_FILL,YELLOW);
fillpoly(12,sistema1);


setcolor(WHITE);
setfillstyle(SOLID_FILL,WHITE);
fillpoly(36,paint1);
fillpoly(5,detallecal2);
fillpoly(7,menu);
fillpoly(5,detallemenu2);

setcolor(BROWN);
setfillstyle(SOLID_FILL,BROWN);
fillpoly(5,detallepaint2);
fillpoly(5,detallepaint4);
fillpoly(5,detallepaint3);
fillpoly(3,detallemenu12);
fillpoly(3,detallemenu13);
fillpoly(3,detallemenu14);
fillpoly(3,detallemenu15);
fillpoly(3,detallemenu16);
fillpoly(3,detallemenu17);
fillpoly(3,detallemenu18);
fillpoly(3,detallemenu19);
fillpoly(3,detallemenu20);
fillpoly(3,detallemenu21);
fillpoly(3,detallemenu22);
fillpoly(3,detallemenu23);

setcolor(MAGENTA);
setfillstyle(SOLID_FILL,MAGENTA);
fillpoly(10,detallepaint21);

setcolor(GREEN);
setfillstyle(SOLID_FILL,GREEN);
fillpoly(5,detallemenu10);
fillpoly(5,detallemenu11);

setcolor(LIGHTCYAN);
setfillstyle(SOLID_FILL,LIGHTCYAN);
fillpoly(13,detallepaint41);

setcolor(YELLOW);
setfillstyle(SOLID_FILL,YELLOW);
fillpoly(29,nota);

setcolor(DARKGRAY);
setfillstyle(SOLID_FILL,DARKGRAY);
fillpoly(5,detallecal3);
fillpoly(5,detallecal4);
fillpoly(5,detallecal5);
fillpoly(5,detallecal6);
fillpoly(5,detallecal7);
fillpoly(5,detallecal8);
fillpoly(5,detallecal9);
fillpoly(5,detallecal10);
fillpoly(5,detallemenu4);
fillpoly(5,detallemenu5);
fillpoly(5,detallemenu6);
fillpoly(5,detallemenu7);
fillpoly(5,detallemenu8);
fillpoly(5,detallemenu9);
fillpoly(5,detallefecha1);
fillpoly(5,detallefecha2);
fillpoly(5,detallehora1);
fillpoly(5,detallehora2);

/*fecha en tiempo real*/
getdate(&fecha);


    sprintf(texto, "%02d/%02d/%d", fecha.da_day, fecha.da_mon, fecha.da_year);


    setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 0);


	outtextxy(544, 419, texto);
	outtextxy(560,403,"Fecha");
	outtextxy(565,438,"Hora");

}

/*logica de click barra de tarea: Redirigir app clickeada*/
void iconos()
{
int pdrive = DETECT, pmode;

	iniciar_raton();
	mostrar_raton();

while (1) {
    int mx, my, click;
    struct tm *tiempo;
    time_t t = time(NULL);

    obtener_posicion_raton(&mx, &my, &click);

    if (click == 1) {
        if (mx >= 225 && mx <= 314 && my >= 393 && my <= 471) {
		ocultar_raton();
		cleardevice();
		funcion_calculadora();
		cleardevice();
		setbkcolor(BLACK);
		fondo_dibujar();
		icono_app();
		iconos_escri();
		mostrar_raton();
        }
	if (mx >= 13 && mx <= 102 && my >= 393 && my <= 471) {
		cleardevice();
		closegraph();
		funcion_DB();
		initgraph(&pdrive, &pmode, "C:\\TC20\\BIN");
		cleardevice();
		setbkcolor(BLACK);
		fondo_dibujar();
		icono_app();
		iconos_escri();
		mostrar_raton();
	}
	if (mx >= 121 && mx <= 210 && my >= 393 && my <= 471){
		ocultar_raton();
		cleardevice();
		funcion_paint();
		cleardevice();
		setbkcolor(BLACK);
		fondo_dibujar();
		icono_app();
		iconos_escri();
		mostrar_raton();
	}

	if (mx >= 329 && mx <= 418 && my >= 393 && my <= 471){
		ocultar_raton();
		cleardevice();
		funcion_notas();
		cleardevice();
		setbkcolor(BLACK);
		fondo_dibujar();
		icono_app();
		iconos_escri();
		mostrar_raton();
	}
	if (mx >= 11 && mx < 104 && my >= 5 && my <= 98) {
		ocultar_raton();
		cleardevice();
		funcion_app();
		cleardevice();
		setbkcolor(BLACK);
		fondo_dibujar();
		icono_app();
		iconos_escri();
		mostrar_raton();
	}
	if (mx >= 433 && mx <= 524 && my >= 393 && my <= 471) {
		ocultar_raton();
		cleardevice();
		funcion_opcionesoo();
		cleardevice();
		setbkcolor(BLACK);
		fondo_dibujar();
		icono_app();
		iconos_escri();
		mostrar_raton();
	}
    }

    if (t != ultimo_tiempo) {
        ultimo_tiempo = t;
        tiempo = localtime(&t);

        sprintf(hora, "%02d:%02d:%02d", tiempo->tm_hour, tiempo->tm_min, tiempo->tm_sec);

        setcolor(DARKGRAY);
        fillpoly(5, detallehora2);

        setcolor(WHITE);
        settextstyle(1, HORIZ_DIR, 1);
        outtextxy(541, 446, hora);
    }

    if (kbhit()) {
        int c = getch();
        if (c == 27) {
        	ocultar_raton();
		delay(100);
		cleardevice();
		apagado_carga();
		delay(100);
                closegraph();
                return;
        } else if (c == 108) {
		ocultar_raton();
		return;
	}
    }

    delay(10); 
}
}

/*funcion principal*/
void funcion_inicio(){

	cleardevice();
	logo_fondo();
	icono_app();
	iconos_escri();
	iconos();
}

#endif