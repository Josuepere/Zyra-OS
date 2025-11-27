#ifndef GAME_H
#define GAME_H

/*librerias necesarias*/
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

union REGS in, out;

#define TABLERO_IZQ 100
#define TABLERO_SPR 70
#define TAMA_CELDA 100
#define TAMA_CUADRI 3

int tablero[TAMA_CUADRI][TAMA_CUADRI];
int jugador = 1;
char jugador1_nombre[32];
char jugador2_nombre[32];

int puntaje1 = 0;
int puntaje2 = 0;

/* Panel / boton (se calculan al iniciar) */
int panel_izq, panel_spr, panel_w, panel_h;
int exit_x, exit_y, exit_w, exit_h;

/*prototipos*/
int mouse_inito();
void mouse_show();
void mouse_status(int *buttons, int *x, int *y);
void hide_mousepi();
void dibujar_tablero();
void celdas_centradas(int i, int j, int *cx, int *cy);
void dibujar_x(int i, int j);
void dibujar_O(int i, int j);
void redibujar_marcas();
void panel_puntos();
void boton_salir();
void limpiarMensajeInferior();
void mostrar_mensaje(const char *msg);
void mostrarReinicio();
int coor_celdas(int x, int y, int *i, int *j);
int ganador();
void reiniciar_tablero();
void pedirTexto(char *destino, int x, int y, int width, int maxLen);
void pantallaInicio(char *p1, char *p2);
void funcion_app();

/*funciones mouse*/
int mouse_inito() {
    in.x.ax = 0;
    int86(0x33, &in, &out);
    return out.x.ax;
}

void mouse_show() {
    in.x.ax = 1; int86(0x33,&in,&out);
}

void mouse_status(int *buttons, int *x, int *y) {
    in.x.ax = 3; int86(0x33,&in,&out);
    *buttons = out.x.bx;
    *x = out.x.cx;
    *y = out.x.dx;
}

void hide_mousepi()
{
    in.x.ax = 2;
    int86(0x33, &in, &out);
}

/*tablero de juego*/
void dibujar_tablero() {
    setcolor(WHITE);

    line(TABLERO_IZQ, TABLERO_SPR,
         TABLERO_IZQ + TAMA_CELDA * TAMA_CUADRI, TABLERO_SPR);

    line(TABLERO_IZQ, TABLERO_SPR + TAMA_CELDA * TAMA_CUADRI,
         TABLERO_IZQ + TAMA_CELDA * TAMA_CUADRI, TABLERO_SPR + TAMA_CELDA * TAMA_CUADRI);

    line(TABLERO_IZQ, TABLERO_SPR,
         TABLERO_IZQ, TABLERO_SPR + TAMA_CELDA * TAMA_CUADRI);

    line(TABLERO_IZQ + TAMA_CELDA * TAMA_CUADRI, TABLERO_SPR,
         TABLERO_IZQ + TAMA_CELDA * TAMA_CUADRI, TABLERO_SPR + TAMA_CELDA * TAMA_CUADRI);

    line(TABLERO_IZQ + TAMA_CELDA, TABLERO_SPR,
         TABLERO_IZQ + TAMA_CELDA, TABLERO_SPR + TAMA_CELDA * TAMA_CUADRI);

    line(TABLERO_IZQ + TAMA_CELDA * 2, TABLERO_SPR,
         TABLERO_IZQ + TAMA_CELDA * 2, TABLERO_SPR + TAMA_CELDA * TAMA_CUADRI);

    line(TABLERO_IZQ, TABLERO_SPR + TAMA_CELDA,
         TABLERO_IZQ + TAMA_CELDA * TAMA_CUADRI, TABLERO_SPR + TAMA_CELDA);

    line(TABLERO_IZQ, TABLERO_SPR + TAMA_CELDA * 2,
         TABLERO_IZQ + TAMA_CELDA * TAMA_CUADRI, TABLERO_SPR + TAMA_CELDA * 2);
}

/* Coordenadas del centro de una celda */
void celdas_centradas(int i, int j, int *cx, int *cy) {
    *cx = TABLERO_IZQ + j*TAMA_CELDA + TAMA_CELDA/2;
    *cy = TABLERO_SPR  + i*TAMA_CELDA + TAMA_CELDA/2;
}

/* Dibujar X y O */
void dibujar_x(int i, int j) {
    int cx, cy, r = TAMA_CELDA/2 - 12;
    celdas_centradas(i,j,&cx,&cy);
    setcolor(RED);
    line(cx - r, cy - r, cx + r, cy + r);
    line(cx - r, cy + r, cx + r, cy - r);
}
void dibujar_O(int i, int j) {
    int cx, cy, r = TAMA_CELDA/2 - 12;
    celdas_centradas(i,j,&cx,&cy);
    setcolor(BLUE);
    circle(cx, cy, r);
}

void redibujar_marcas() {
    int i,j;
    for (i=0;i<TAMA_CUADRI;i++) for (j=0;j<TAMA_CUADRI;j++) {
        if (tablero[i][j] == 1) dibujar_x(i,j);
        else if (tablero[i][j] == 2) dibujar_O(i,j);
    }
}

/* Dibuja las "tarjetas" de puntuacion a la derecha del tablero */
void panel_puntos() {
    int card_w = panel_w;
    int card_h = panel_h / 2; /* cada tarjeta ocupa la mitad del panel */
    int gap = 10;
    char buf[32];
    int y2 = panel_spr + card_h + gap;
    int padding = 8;
    int line_spacing = (card_h - 2*padding) / 3;
    
    settextjustify(LEFT_TEXT, TOP_TEXT);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    /* Tarjeta Jugador 1 */
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(panel_izq, panel_spr, panel_izq + card_w, panel_spr + card_h);
    setcolor(WHITE);
    rectangle(panel_izq, panel_spr, panel_izq + card_w, panel_spr + card_h);

    outtextxy(panel_izq + padding, panel_spr + padding, "Jugador 1 (X):");
    outtextxy(panel_izq + padding, panel_spr + padding + line_spacing, jugador1_nombre);
    sprintf(buf, "Puntos: %d", puntaje1);
    outtextxy(panel_izq + padding, panel_spr + padding + 2*line_spacing, buf);

    /* Tarjeta Jugador 2 */
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(panel_izq, y2, panel_izq + card_w, y2 + card_h);
    setcolor(WHITE);
    rectangle(panel_izq, y2, panel_izq + card_w, y2 + card_h);

    outtextxy(panel_izq + padding, y2 + padding, "Jugador 2 (O):");
    outtextxy(panel_izq + padding, y2 + padding + line_spacing, jugador2_nombre);
    sprintf(buf, "Puntos: %d", puntaje2);
    outtextxy(panel_izq + padding, y2 + padding + 2*line_spacing, buf);
}


/* Dibuja boton de salir en la esquina superior derecha */
void boton_salir() {
    setcolor(RED);
    rectangle(exit_x, exit_y, exit_x + exit_w, exit_y + exit_h);
    outtextxy(exit_x + exit_w/2 - 3, exit_y + exit_h/2 - 3, "X");
}

/* Borra solo la zona de mensaje inferior (sin tocar el tablero y panel) */
void limpiarMensajeInferior() {
    int left = TABLERO_IZQ - 10;
    int right = TABLERO_IZQ + TAMA_CELDA*TAMA_CUADRI + 10 + panel_w + 20;
    int top = TABLERO_SPR + TAMA_CELDA*TAMA_CUADRI + 10;
    int bottom = top + 70;
    setfillstyle(SOLID_FILL, BLACK);
    bar(left, top, right, bottom);
}

/* Muestra mensaje centrado en la zona inferior */
void mostrar_mensaje(const char *msg) {
    limpiarMensajeInferior();
	setcolor(WHITE);
    /* centrar respecto al tablero solamente */
    outtextxy(TABLERO_IZQ + TAMA_CELDA*TAMA_CUADRI/2 - 50,
              TABLERO_SPR + TAMA_CELDA*TAMA_CUADRI + 30, msg);
}

/* Muestra mensaje para reiniciar */
void mostrarReinicio() {
    setcolor(WHITE);
    outtextxy(TABLERO_IZQ + TAMA_CELDA*TAMA_CUADRI/2 - 100,
              TABLERO_SPR + TAMA_CELDA*TAMA_CUADRI + 50,
              "Presiona ENTER para reiniciar");
}

int coor_celdas(int x, int y, int *i, int *j) {
    if (x < TABLERO_IZQ || x > TABLERO_IZQ + TAMA_CELDA*TAMA_CUADRI ||
        y < TABLERO_SPR  || y > TABLERO_SPR  + TAMA_CELDA*TAMA_CUADRI)
        return 0;
    *j = (x - TABLERO_IZQ) / TAMA_CELDA;
    *i = (y - TABLERO_SPR) / TAMA_CELDA;
    return 1;
}

/*logica del ganador*/
int ganador() {
    int i,j, full = 1;
    /* filas */
    for (i=0;i<TAMA_CUADRI;i++)
        if (tablero[i][0] != 0 &&
            tablero[i][0] == tablero[i][1] &&
            tablero[i][1] == tablero[i][2]) return tablero[i][0];
    /* columnas */
    for (j=0;j<TAMA_CUADRI;j++)
        if (tablero[0][j] != 0 &&
            tablero[0][j] == tablero[1][j] &&
            tablero[1][j] == tablero[2][j]) return tablero[0][j];
    /* diagonales */
    if (tablero[0][0] != 0 && tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]) return tablero[0][0];
    if (tablero[0][2] != 0 && tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0]) return tablero[0][2];
    /* empate? */
    for (i=0;i<TAMA_CUADRI;i++) for (j=0;j<TAMA_CUADRI;j++) if (tablero[i][j] == 0) full = 0;
    if (full) return 3;
    return 0;
}

/*reiniciar tablero o juego*/
void reiniciar_tablero() {
    int i,j;
    for (i=0;i<TAMA_CUADRI;i++) for (j=0;j<TAMA_CUADRI;j++) tablero[i][j] = 0;
    jugador = 1;
    cleardevice();
    dibujar_tablero();
    redibujar_marcas();
    panel_puntos();
    boton_salir();
}

/* input solicitud nombres usuarios */
void pedirTexto(char *destino, int x, int y, int width, int maxLen) {
    int c, len = 0;
    destino[0] = '\0';

    /* Dibuja borde de la caja */
    setcolor(WHITE);
    rectangle(x, y, x + width, y + 22);

    /* Inicial: limpiar interior y posicionar cursor visual */
    setfillstyle(SOLID_FILL, BLACK);
    bar(x + 2, y + 2, x + width - 2, y + 20);

    while (1) {
        c = getch();

        if (c == 13) { /* ENTER */
            destino[len] = '\0';
            break;
        } else if (c == 8) { /* BACKSPACE */
            if (len > 0) {
                len--;
                destino[len] = '\0';
                /* Limpiar solo interior */
                setfillstyle(SOLID_FILL, BLACK);
                bar(x + 3, y + 3, x + width - 3, y + 19);
                outtextxy(x + 6, y + 5, destino);
            }
        } else if (c >= 32 && c <= 126) { /* caracter imprimible */
            if (len < maxLen - 1 && (int)strlen(destino) < maxLen - 1) {
                destino[len++] = (char)c;
                destino[len] = '\0';
                outtextxy(x + 6, y + 5, destino);
            }
        }
    }
}

/*pantalla inicio juego*/
void pantallaInicio(char *p1, char *p2) {
    int winW = getmaxx();
    int winH = getmaxy();
    int boxW = 220;
    int centerX = (winW - boxW) / 2;
    cleardevice();

    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3); /* titulo grande */
    settextjustify(CENTER_TEXT, TOP_TEXT);
    outtextxy(winW/2, 50, "TRES  EN  LINEA");

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    settextjustify(LEFT_TEXT, TOP_TEXT);

    outtextxy(centerX, 120, "Nombre del Jugador 1 (X):");
    pedirTexto(p1, centerX, 140, boxW, 30);

    outtextxy(centerX, 200, "Nombre del Jugador 2 (O):");
    pedirTexto(p2, centerX, 220, boxW, 30);

    /* Mensaje de confirmacion */
    settextjustify(CENTER_TEXT, TOP_TEXT);
    outtextxy(winW/2, 280, "Presiona cualquier tecla para comenzar...");
    getch();
}

/*funcion principal*/
void funcion_app() {
    int buttons=0, last_buttons = 0, mx=0, my=0;
    int ci, cj, winner;
    char msg[128];

    cleardevice();

    /* Pantalla de inicio */
    pantallaInicio(jugador1_nombre, jugador2_nombre);

    /* Calcular posiciones del panel y el boton */
    {
        int winW = getmaxx();
        int winH = getmaxy();
        panel_w = 180;
        panel_h = 140;
        /* colocar el panel ligeramente alineado con el tablero */
        panel_izq = TABLERO_IZQ + TAMA_CELDA*TAMA_CUADRI + 30;
        panel_spr = TABLERO_SPR + 10;

        /* boton X en esquina superior derecha */
        exit_w = 28;
        exit_h = 18;
        exit_x = winW - exit_w - 10;
        exit_y = 8;
    }

    mouse_show();

    /* Iniciar tablero y panel */
    reiniciar_tablero();
    sprintf(msg, "Turno: %s (X)", jugador1_nombre);
    mostrar_mensaje(msg);

    /* dibujar panel y boton iniciales */
    panel_puntos();
    boton_salir();

    /* Bucle principal */
    while (1) {
        mouse_status(&buttons, &mx, &my);

        /* Si se hizo click dentro del boton X salir */
        if ((buttons & 1) && !(last_buttons & 1)) {
            if (mx >= exit_x && mx <= exit_x + exit_w &&
                my >= exit_y && my <= exit_y + exit_h) {
		hide_mousepi();
                break; /* salir del juego */
            }
        }

        /* Detectar click izquierdo dentro del tablero */
        if ((buttons & 1) && !(last_buttons & 1)) {
            if (coor_celdas(mx, my, &ci, &cj)) {
                if (tablero[ci][cj] == 0) {
                    tablero[ci][cj] = jugador;
                    if (jugador == 1) dibujar_x(ci,cj);
                    else dibujar_O(ci,cj);

                    winner = ganador();

                    if (winner == 1 || winner == 2) {
                        /* Sumar puntos al ganador */
                        if (winner == 1) puntaje1++;
                        else puntaje2++;

                        /* Mostrar ganador y pedir ENTER para reiniciar */
                        limpiarMensajeInferior();
                        dibujar_tablero();
                        redibujar_marcas();
                        panel_puntos();
                        boton_salir();

                        sprintf(msg, "Ganador: %s", (winner == 1) ? jugador1_nombre : jugador2_nombre);
                        mostrar_mensaje(msg);
                        mostrarReinicio();

                        /* Esperar ENTER */
                        while (1) {
                            if (kbhit()) {
                                int k = getch();
                                if (k == 13) break;
                            }
                        }
                        reiniciar_tablero();
                        panel_puntos();
                        boton_salir();
                        sprintf(msg, "Turno: %s (X)", jugador1_nombre);
                        mostrar_mensaje(msg);
                        continue;
                    } else if (winner == 3) {
                        /* Empate: no sumar puntos */
                        limpiarMensajeInferior();
                        dibujar_tablero();
                        redibujar_marcas();
                        panel_puntos();
                        boton_salir();
                        mostrar_mensaje("Empate!");
                        mostrarReinicio();

                        while (1) {
                            if (kbhit()) {
                                int k = getch();
                                if (k == 13) break;
                            }
                        }
                        reiniciar_tablero();
                        panel_puntos();
                        boton_salir();
                        sprintf(msg, "Turno: %s (X)", jugador1_nombre);
                        mostrar_mensaje(msg);
                        continue;
                    }

                    /* Cambiar turno y mostrar */
                    jugador = (jugador == 1) ? 2 : 1;
                    sprintf(msg, "Turno: %s", (jugador == 1) ? jugador1_nombre : jugador2_nombre);
                    mostrar_mensaje(msg);
                }
            }
        }

        last_buttons = buttons;
        delay(20);
    }
    return;
}

#endif