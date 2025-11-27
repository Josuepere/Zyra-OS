#ifndef CALCULA_H
#define CALCULA_H

/*librerias necesarias*/
#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

union REGS entrada, salida;
char entradaTexto[30] = "0";
int operacion = 0;
float numero1 = 0.0, numero2 = 0.0, resultado = 0.0;

/*prototipos*/
int iniciarRaton();
void mostrarRaton();
void ocultarRaton();
void obtenerPosicionRaton(int *x, int *y, int *boton);
void copiarSeguro(char *destino, const char *origen, int n);
void dibujarBoton3D(int x1,int y1,int x2,int y2,const char *etiqueta,int presionado);
void dibujarInterfaz();
void actualizarPantalla(char *texto);
int clicDentro(int mx, int my, int x1, int y1, int x2, int y2);
int procesarClic(int mx, int my);
void procesarTecla(int tecla);
void funcion_calculadora();

/*  Funciones del raton  */
int iniciarRaton() {
    entrada.x.ax = 0;
    int86(0x33, &entrada, &salida);
    return salida.x.ax;
}
void mostrarRaton() { 
    entrada.x.ax = 1; 
    int86(0x33, &entrada, &salida); 
}
void ocultarRaton() { 
    entrada.x.ax = 2; 
    int86(0x33, &entrada, &salida); 
}
void obtenerPosicionRaton(int *x, int *y, int *boton) {
    entrada.x.ax = 3;
    int86(0x33, &entrada, &salida);
    *boton = salida.x.bx; *x = salida.x.cx; *y = salida.x.dx;
}

void copiarSeguro(char *destino, const char *origen, int n) {
    int i;
    for (i = 0; i < n-1 && origen[i] != '\0'; ++i) destino[i] = origen[i];
    destino[i] = '\0';
}

/* Dibuja un boton */
void dibujarBoton3D(int x1,int y1,int x2,int y2,const char *etiqueta,int presionado)
{
    setfillstyle(SOLID_FILL, WHITE);
    bar(x1, y1, x2, y2);

    if (!presionado) {
        setcolor(LIGHTGRAY);
        rectangle(x1, y1, x2, y2);
    } else {
        setcolor(DARKGRAY);
        rectangle(x1, y1, x2, y2);
    }

    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy((x1+x2)/2 - textwidth((char*)etiqueta)/2,
              (y1+y2)/2 - textheight((char*)etiqueta)/2,
              (char*)etiqueta);
}

/*  interfaz PR */
void dibujarInterfaz() {
    setbkcolor(DARKGRAY);
    cleardevice();

    setcolor(RED);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(200, 10, "Calculadora Zyra");

    setfillstyle(SOLID_FILL, RED);
    bar(600, 10, 630, 35);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(610, 15, "X");

    /* P display */
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(26, 50, 614, 130);
    setfillstyle(SOLID_FILL, WHITE);
    bar(30, 54, 610, 126);
    setcolor(LIGHTGRAY);
    rectangle(30, 54, 610, 126);

    /* Botones */
    dibujarBoton3D(30,210,160,260,"7",0);
    dibujarBoton3D(180,210,310,260,"8",0);
    dibujarBoton3D(330,210,460,260,"9",0);
    dibujarBoton3D(480,210,610,260,"/",0);

    dibujarBoton3D(30,280,160,330,"4",0);
    dibujarBoton3D(180,280,310,330,"5",0);
    dibujarBoton3D(330,280,460,330,"6",0);
    dibujarBoton3D(480,280,610,330,"x",0);

    dibujarBoton3D(30,350,160,400,"1",0);
    dibujarBoton3D(180,350,310,400,"2",0);
    dibujarBoton3D(330,350,460,400,"3",0);
    dibujarBoton3D(480,350,610,400,"-",0);

    dibujarBoton3D(30,420,160,470,"0",0);
    dibujarBoton3D(180,420,310,470,".",0);
    dibujarBoton3D(330,420,460,470,"=",0);
    dibujarBoton3D(480,420,610,470,"+",0);

	dibujarBoton3D(480,150,610,200,"AC",0);

	dibujarBoton3D(330,150,460,200,"DEL",0);
}

/*  Actualiza txt */
void actualizarPantalla(char *texto) {
    int anchoMax;
    char buffer[30];
    int i, len;

    setfillstyle(SOLID_FILL, WHITE);
    bar(32, 56, 608, 124);

    anchoMax = 570;
    copiarSeguro(buffer, texto, sizeof(buffer));

    while (textwidth(buffer) > anchoMax && strlen(buffer) > 1) {
        len = strlen(buffer);
        for (i = 0; i < len; ++i) buffer[i] = buffer[i+1];
        buffer[len-1] = '\0';
    }

    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(600 - textwidth(buffer), 80, buffer);
}

/* Es si el clic esta dentro de area mae */
int clicDentro(int mx, int my, int x1, int y1, int x2, int y2) {
    return (mx >= x1 && mx <= x2 && my >= y1 && my <= y2);
}

/*  clic  */
int procesarClic(int mx, int my) {

    if (clicDentro(mx,my,600,10,630,35)){
	cleardevice();
	return 1;
    }

    /* Boton "C" (limpiar todo) */
    if (clicDentro(mx,my,480,150,610,200)) {
        strcpy(entradaTexto, "0");
        numero1 = numero2 = resultado = 0;
        operacion = 0;
        actualizarPantalla(entradaTexto);
        return 0;
    }

    /* Boton "DZY" (retroceso) */
    if (clicDentro(mx,my,330,150,460,200)) {
        int len = strlen(entradaTexto);
        if (len > 0) entradaTexto[len - 1] = '\0';
        if (strlen(entradaTexto) == 0) strcpy(entradaTexto, "0");
        actualizarPantalla(entradaTexto);
        return 0;
    }

    if (clicDentro(mx,my,30,210,160,260)) {
        if (strcmp(entradaTexto,"0")==0) strcpy(entradaTexto,"7"); else strcat(entradaTexto,"7");
    }
    else if (clicDentro(mx,my,180,210,310,260)) {
        if (strcmp(entradaTexto,"0")==0) strcpy(entradaTexto,"8"); else strcat(entradaTexto,"8");
    }
    else if (clicDentro(mx,my,330,210,460,260)) {
        if (strcmp(entradaTexto,"0")==0) strcpy(entradaTexto,"9"); else strcat(entradaTexto,"9");
    }
    else if (clicDentro(mx,my,480,210,610,260)) { operacion=4; numero1=atof(entradaTexto); strcpy(entradaTexto,""); }

    else if (clicDentro(mx,my,30,280,160,330)) {
        if (strcmp(entradaTexto,"0")==0) strcpy(entradaTexto,"4"); else strcat(entradaTexto,"4");
    }
    else if (clicDentro(mx,my,180,280,310,330)) {
        if (strcmp(entradaTexto,"0")==0) strcpy(entradaTexto,"5"); else strcat(entradaTexto,"5");
    }
    else if (clicDentro(mx,my,330,280,460,330)) {
        if (strcmp(entradaTexto,"0")==0) strcpy(entradaTexto,"6"); else strcat(entradaTexto,"6");
    }
    else if (clicDentro(mx,my,480,280,610,330)) { operacion=3; numero1=atof(entradaTexto); strcpy(entradaTexto,""); }

    else if (clicDentro(mx,my,30,350,160,400)) {
        if (strcmp(entradaTexto,"0")==0) strcpy(entradaTexto,"1"); else strcat(entradaTexto,"1");
    }
    else if (clicDentro(mx,my,180,350,310,400)) {
        if (strcmp(entradaTexto,"0")==0) strcpy(entradaTexto,"2"); else strcat(entradaTexto,"2");
    }
    else if (clicDentro(mx,my,330,350,460,400)) {
        if (strcmp(entradaTexto,"0")==0) strcpy(entradaTexto,"3"); else strcat(entradaTexto,"3");
    }
    else if (clicDentro(mx,my,480,350,610,400)) { operacion=2; numero1=atof(entradaTexto); strcpy(entradaTexto,""); }

    else if (clicDentro(mx,my,30,420,160,470)) {
        if (strcmp(entradaTexto,"0")==0) strcpy(entradaTexto,"0"); else strcat(entradaTexto,"0");
    }
    else if (clicDentro(mx,my,180,420,310,470)) {
        if (strchr(entradaTexto, '.') == NULL) {
            if (strcmp(entradaTexto,"0")==0) strcpy(entradaTexto,"0."); else strcat(entradaTexto,".");
        }
    }
else if (clicDentro(mx,my,330,420,460,470)) {
    numero2 = atof(entradaTexto);

    if (operacion == 4 && numero2 == 0) {
        setfillstyle(SOLID_FILL, WHITE);
		bar(32, 56, 608, 124);
        setcolor(RED);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
		outtextxy(200, 80, "Error: The Syntax");
		delay(1500);
		strcpy(entradaTexto, "0");
        operacion = 0;
        actualizarPantalla(entradaTexto);
        return 0;
    }
    switch(operacion) {
        case 1: resultado = numero1 + numero2; break;
        case 2: resultado = numero1 - numero2; break;
        case 3: resultado = numero1 * numero2; break;
        case 4: resultado = numero1 / numero2; break;
    }

    sprintf(entradaTexto, "%.2f", resultado);
    actualizarPantalla(entradaTexto);
}


    else if (clicDentro(mx,my,480,420,610,470)) { 
        operacion=1; numero1=atof(entradaTexto); 
        strcpy(entradaTexto,""); 
    }

    actualizarPantalla(entradaTexto);
    return 0;
}

void procesarTecla(int tecla) {
    char s[3];
    s[1] = '\0';
    s[2] = '\0';

    /* Digitos */
    if (tecla >= '0' && tecla <= '9') {
        /* reemplaza "0" inicial en vez de concatenar */
        if (strcmp(entradaTexto, "0") == 0) {
            s[0] = (char)tecla;
            strcpy(entradaTexto, s);
        } else {
            s[0] = (char)tecla;
            strcat(entradaTexto, s);
        }
    }
    else if (tecla == '.') {
        /* solo permitir un punto */
        if (strchr(entradaTexto, '.') == NULL) {
            strcat(entradaTexto, ".");
        }
    }
    else if (tecla == '+' || tecla == '-' || tecla == '*' || tecla == '/') {
        numero1 = atof(entradaTexto);
        strcpy(entradaTexto, "0");
        if (tecla == '+') operacion = 1;
        else if (tecla == '-') operacion = 2;
        else if (tecla == '*') operacion = 3;
        else if (tecla == '/') operacion = 4;
    }
    else if (tecla == '=' || tecla == 13) { /* Enter o '=' */
        numero2 = atof(entradaTexto);
        switch(operacion) {
            case 1: resultado = numero1 + numero2; break;
            case 2: resultado = numero1 - numero2; break;
            case 3: resultado = numero1 * numero2; break;
            case 4: resultado = numero2 != 0 ? numero1 / numero2 : 0; break;
            default: resultado = atof(entradaTexto); break;
        }
        sprintf(entradaTexto, "%.2f", resultado);
    }
    else if (tecla == 8) {  /* borrar */
        int len = strlen(entradaTexto);
        if (len > 0) {
            entradaTexto[len - 1] = '\0';
            if (strlen(entradaTexto) == 0) strcpy(entradaTexto, "0");
        }
    }
    else if (tecla == 'c' || tecla == 'C') { /* limpiar */
        strcpy(entradaTexto, "0");
        operacion = 0; numero1 = numero2 = resultado = 0;
    }

    actualizarPantalla(entradaTexto);
}

/* Programa principal */
void funcion_calculadora() {
    int mx, my, boton;

    if (!iniciarRaton()) {
        getch(); closegraph(); return;
    }

    dibujarInterfaz();
    mostrarRaton();
    actualizarPantalla(entradaTexto);

    while (1) {
        obtenerPosicionRaton(&mx, &my, &boton);
        if (boton == 1) {
            if (procesarClic(mx, my) == 1){
		ocultarRaton();
		return;
	    }
            delay(200);
        }

        /*deteccion del teclado compatible*/
        if (kbhit()) {
            int c = getch();   
            if (c == 0) {
                getch();
            } else {
                procesarTecla(c);
            }
            delay(80);
        }
    }

    ocultarRaton();
}

#endif