#ifndef CARGA_H
#define CARGA_H

/*librerias necesarias*/
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include <bloqueo.h>

/*prototipos*/
void logo();
void carga_funcion();

/*funcion logo: imprime el logo del sistema operativo (ZYRA)*/
void logo(){

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

	char texto[50];

	int i;

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


	setcolor(WHITE);
	rectangle(170,360,470,390);
	outtextxy(180,350,"Cargando..");

	/*Simulacion de barra de carga*/
	for(i = 1; i <= 100; i++){


		if(i == 100){

			setcolor(BLACK);
			setfillstyle(SOLID_FILL,BLACK);
			fillpoly(5,cuadro);

			setcolor(GREEN);
			outtextxy(180,350," Carga Completada!");


			}
		setfillstyle(SOLID_FILL, i % 15);
		bar(171,361,170 + (3 * i), 389);

		setfillstyle(SOLID_FILL,BLACK);
		bar(290,395,320,410);

		sprintf(texto, "%d%%",i);
		setcolor(WHITE);
		outtextxy(300,400,texto);
		delay(40);

	}



}

/*funcion principal*/
void carga_funcion(){
	logo();
	delay(1500);
	funcion_bloqueo();
}

#endif