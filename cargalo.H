#ifndef CARGALO_H
#define CARGALO_H

/*librerias necesarias*/
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include <math.h>   
#define PI 3.14159265

/*prototipos*/
void carga_pantalla();
void logo_de_carga();
void animacion_carga();

/*simulacion de carga (circular)*/
void carga_pantalla()
{
    int centroX = 315;
    int centroY = 400;  
    int radio = 28;
    int puntos = 8;
    int activo = 0;
    int i;
    int j;
    int iteraciones = 3000 / 160; 

    for (j = 0; j < iteraciones; j++)
    {
        setcolor(WHITE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        outtextxy(280, 435, "Iniciando...");

        for (i = 0; i < puntos; i++)
        {
            double ang = (360.0 / puntos) * i;
            double rad = ang * 3.14159265 / 180.0;

            int px = centroX + (int)(radio * cos(rad));
            int py = centroY + (int)(radio * sin(rad));

            if (i == activo)
            {
                setcolor(WHITE);
                setfillstyle(SOLID_FILL, WHITE);
            }
            else
            {
                setcolor(BLACK);
                setfillstyle(SOLID_FILL, BLACK);
            }

            fillellipse(px, py, 3, 3);
        }

        delay(160);

        activo++;
        if (activo >= puntos)
            activo = 0;
    }
    return;
}

/*logo*/
void logo_de_carga()
{
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

/*funcion principal*/
void animacion_carga()
{
    logo_de_carga();
    carga_pantalla();

}

#endif