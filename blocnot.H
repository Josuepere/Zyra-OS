#ifndef BLOCNOT_RENOMBRADO_H
#define BLOCNOT_RENOMBRADO_H

/*librerias necesarias */
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>


#define MAX_BUFFER_TEXTO 500
char bufferTexto[MAX_BUFFER_TEXTO];         
char nombreArchEntrada[50];                 
char nombreArchActual[50];                  
union REGS regsIn, regsOut;                 
#define COOR_X1_AREA 10
#define COOR_Y1_AREA 70
#define COOR_X2_AREA 574
#define COOR_Y2_AREA 478

/* Codigos de Botones */
#define COD_BTN_NINGUNO 0
#define COD_BTN_NUEVO 1
#define COD_BTN_GUARDAR 2
#define COD_BTN_BORRAR 3
#define COD_BTN_ABRIR 4
#define COD_BTN_SALIR 5

/* Prototipos de funciones */
void mostrarMensajeCuadro(const char *msg, int duracion_ms);
void mostrarMensajeTemporal(const char *msg, int x_coor, int y_coor, int color_texto, int color_fondo, int tiempo_ms);
int pedirNombreArchivo(char nombre_arch_salida[]);
void guardarContenido(char nombre_arch_guardar[], char contenido_a_guardar[]);
int eliminarArchivo(char nombre_arch_a_borrar[]);
void crearArchivoVacio(char nombre_arch_nuevo[]);
void dibujar_interfaz_app();
void limpiarZonaEdicion();
int cargarArchivo(char nombre_archivo[]);
void inicializar_raton();
void mostrar_puntero_raton();
void mostrarContenido(char contenido_texto []);
void obtener_estado_raton(int *x, int *y, int *boton);
void ocur_raton();
void mover(int x, int y);
void limpiar_buffer_teclado();
void funcion_notas();

/* funciones mouse*/

void inicializar_raton() {
    regsIn.x.ax = 0;
    int86(0x33, &regsIn, &regsOut);
}

void mostrar_puntero_raton() {
    regsIn.x.ax = 1;
    int86(0x33, &regsIn, &regsOut);
}

void obtener_estado_raton(int *x, int *y, int *boton) {
    regsIn.x.ax = 3;
    int86(0x33, &regsIn, &regsOut);
    *boton = regsOut.x.bx;
    *x = regsOut.x.cx;
    *y = regsOut.x.dx;
}

void mover(int x, int y){
	regsIn.x.ax = 4;
	regsIn.x.cx = x;
	regsIn.x.dx = y;
	int86(0x33, &regsIn, &regsOut);
}

void ocur_raton() {
    regsIn.x.ax = 2;
    int86(0x33, &regsIn, &regsOut);
}

void mostrarMensajeCuadro(const char *msg, int duracion_ms) { 
    int ancho = textwidth(msg) + 40;
    int alto  = textheight(msg) + 30;

    int x_ini = (639 - ancho) / 2;
    int y_ini = (479 - alto) / 2;
    int x_fin = x_ini + ancho;
    int y_fin = y_ini + alto;

    
    unsigned long size_buffer = imagesize(x_ini, y_ini, x_fin, y_fin);
    void *backup_fondo = malloc(size_buffer);
    if (!backup_fondo) return;
    getimage(x_ini, y_ini, x_fin, y_fin, backup_fondo);

    
    /* Dibujar el cuadro */
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(x_ini, y_ini, x_fin, y_fin);

    setcolor(BLACK);
    rectangle(x_ini, y_ini, x_fin, y_fin);

    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(x_ini + 10, y_ini + 7, msg);

    
    /* Esperar si se especifica una duracion */
    if (duracion_ms > 0) delay(duracion_ms);

    
    /* Restaurar el fondo */
    putimage(x_ini, y_ini, backup_fondo, COPY_PUT);
    free(backup_fondo);
}


void mostrarMensajeTemporal(const char *msg, int x_coor, int y_coor, int color_texto, int color_fondo, int tiempo_ms) 
{
    int ancho_msg = textwidth(msg) + 10;
    int alto_msg  = textheight(msg) + 6;

    
    void *buffer_temporal;
    unsigned long tamano_buffer;

    tamano_buffer = imagesize(x_coor, y_coor, x_coor + ancho_msg, y_coor + alto_msg);
    buffer_temporal = malloc(tamano_buffer);
    if (buffer_temporal == NULL)
        return;

    
    /* Guardar el fondo */
    getimage(x_coor, y_coor, x_coor + ancho_msg, y_coor + alto_msg, buffer_temporal);

    /* Dibujar fondo del mensaje */
    setcolor(color_fondo);
    setfillstyle(SOLID_FILL, color_fondo);
    bar(x_coor, y_coor, x_coor + ancho_msg, y_coor + alto_msg);

    /* Dibujar el texto */
    setcolor(color_texto);
    outtextxy(x_coor + 5, y_coor + 3, msg);

    
    /* Esperar */
    delay(tiempo_ms);

    
    /* Restaurar el fondo */
    putimage(x_coor, y_coor, buffer_temporal, COPY_PUT);
    free(buffer_temporal);
}


void limpiar_buffer_teclado() {
    while (kbhit()) getch();
}

/* pedirNombreArchivo: devuelve 1 si se confirmo con ENTER, 0 si se cancelo con ESC */
int pedirNombreArchivo(char nombre_arch_salida[]) { /* Antes: capturarNombre */

    /* Diseño del cuadro */
    int marco_X1 = 120, marco_Y1 = 120;
    int marco_X2 = 520, marco_Y2 = 260;

    int TITULO_Y = marco_Y1 + 12;
    int caja_X1 = marco_X1 + 40;
    int caja_Y1 = marco_Y1 + 70;
    int caja_X2 = marco_X2 - 40;
    int caja_Y2 = caja_Y1 + 30;

    char tecla, caracter[2] = {0};
    int indice = 0;
    int ancho_max_texto;

    /* Guardar fondo */
    unsigned long tamano_fondo = imagesize(marco_X1, marco_Y1, marco_X2, marco_Y2);
    void *buffer_fondo = malloc(tamano_fondo);
    if (!buffer_fondo) return 0;

    getimage(marco_X1, marco_Y1, marco_X2, marco_Y2, buffer_fondo);

    /* Dibujar ventana */
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(marco_X1, marco_Y1, marco_X2, marco_Y2);

    setcolor(BLACK);
    rectangle(marco_X1, marco_Y1, marco_X2, marco_Y2);

    setcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(marco_X1 + 20, TITULO_Y, "Ingrese nombre archivo");

    /* Caja de entrada */
    setfillstyle(SOLID_FILL, WHITE);
    bar(caja_X1, caja_Y1, caja_X2, caja_Y2);
    setcolor(BLACK);
    rectangle(caja_X1, caja_Y1, caja_X2, caja_Y2);

    /* Loop de ingreso */
    while (1) {
        if (kbhit()) {
            tecla = getch();

            if (tecla == 27) { /* ESC */
                putimage(marco_X1, marco_Y1, buffer_fondo, COPY_PUT);
                free(buffer_fondo);
                nombre_arch_salida[0] = '\0';
                return 0;
            }

            if (tecla == 13) { /* ENTER */
                if (indice > 0) {
                    strcat(nombre_arch_salida, ".txt");
                    putimage(marco_X1, marco_Y1, buffer_fondo, COPY_PUT);
                    free(buffer_fondo);
                    return 1;
                }
            }

            if (tecla == 8 && indice > 0) { /* BORRAR */
                indice--;
                nombre_arch_salida[indice] = '\0';

                /* borrar ultima letra y actualizar */
                setfillstyle(SOLID_FILL, WHITE);
                bar(caja_X1, caja_Y1, caja_X2, caja_Y2);
                outtextxy(caja_X1 + 6, caja_Y1 + 8, nombre_arch_salida);
            }

            if (tecla >= 32 && tecla <= 126) { /* Caracter imprimible */
                caracter[0] = tecla; caracter[1] = '\0';
                ancho_max_texto = caja_X2 - caja_X1 - 10;
                if (textwidth(nombre_arch_salida) + textwidth(caracter) <= ancho_max_texto) {
                    nombre_arch_salida[indice++] = tecla;
                    nombre_arch_salida[indice] = '\0';

                    setfillstyle(SOLID_FILL, WHITE);
                    bar(caja_X1, caja_Y1, caja_X2, caja_Y2);
                    outtextxy(caja_X1 + 6, caja_Y1 + 8, nombre_arch_salida);
                }
            }
        }

        delay(10);
    }

    return 0;
}
 
int eliminarArchivo(char nombre_arch_a_borrar[]) { 
    if (remove(nombre_arch_a_borrar) == 0) {
        return 1;
    } else {
        return 0;
    }
}

/* editarContenido: devuelve un codigo de boton si el usuario hizo click en la barra superior */
int editarContenido(char contenido_buffer[]) {

    int longitud_texto, posicion_cursor, i, j, k;
    int x_cursor, y_cursor;
    int ancho_caracter, alto_caracter, ancho_char;
    char caracter_tecla, buffer_char[2];
    int pos_linea, columna;
    int fin_linea_prev, inicio_linea_prev, inicio_linea_sig, fin_linea_sig;
    int inicio_linea_actual;
    int margen_izq = COOR_X1_AREA, margen_der = COOR_X2_AREA, limite_inf = COOR_Y2_AREA;
    int boton_raton, mouse_x, mouse_y;
    int necesita_redibujar;
    int x_cursor_prev = -1, y_cursor_prev = -1;

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(BLACK);
    buffer_char[1] = '\0';

    ancho_caracter = textwidth("A");
    alto_caracter = textheight("A");

    longitud_texto = strlen(contenido_buffer);
    i = longitud_texto;
    posicion_cursor = i;

    while (1) {

        /* Calcular posicion actual del cursor */
        x_cursor = COOR_X1_AREA;
        y_cursor = COOR_Y1_AREA;

        for (k = 0; k < posicion_cursor; k++) {
            if (contenido_buffer[k] == '\n') {
                y_cursor += alto_caracter + 6;
                x_cursor = COOR_X1_AREA;
            } else {
                buffer_char[0] = contenido_buffer[k];
                x_cursor += textwidth(buffer_char);

                /* salto de linea automatico */
                if (x_cursor > COOR_X2_AREA) {
                    y_cursor += alto_caracter + 6;
                    x_cursor = COOR_X1_AREA;
                }
            }
        }

        /* borrar cursor anterior */
        if (x_cursor_prev != -1 && y_cursor_prev != -1) {
            setcolor(WHITE);
            line(x_cursor_prev, y_cursor_prev, x_cursor_prev, y_cursor_prev + alto_caracter);
        }

        /* dibujar cursor */
        setcolor(BLACK);
        line(x_cursor, y_cursor, x_cursor, y_cursor + alto_caracter);

        x_cursor_prev = x_cursor;
        y_cursor_prev = y_cursor;

        /* revisar click en botones */
        obtener_estado_raton(&mouse_x, &mouse_y, &boton_raton);

        if (boton_raton == 1) {

            int codigo_ret = COD_BTN_NINGUNO;

            if (mouse_x >= 1   && mouse_x <= 127 && mouse_y >= 1  && mouse_y <= 63) codigo_ret = COD_BTN_NUEVO;
            else if (mouse_x >= 129 && mouse_x <= 255 && mouse_y >= 1  && mouse_y <= 63) codigo_ret = COD_BTN_GUARDAR;
            else if (mouse_x >= 257 && mouse_x <= 382 && mouse_y >= 1  && mouse_y <= 63) codigo_ret = COD_BTN_BORRAR;
            else if (mouse_x >= 384 && mouse_x <= 510 && mouse_y >= 1  && mouse_y <= 63) codigo_ret = COD_BTN_ABRIR;
            else if (mouse_x >= 576 && mouse_x <= 638 && mouse_y >= 65 && mouse_y <= 190) codigo_ret = COD_BTN_SALIR;

            if (codigo_ret != COD_BTN_NINGUNO) {

                delay(100);

                /* esperar a que suelte el boton */
                do {
                    obtener_estado_raton(&mouse_x, &mouse_y, &boton_raton);
                    delay(10);
                } while (boton_raton == 1);

                return codigo_ret;
            }
        }

        /* teclas */
        if (kbhit()) {

            caracter_tecla = getch();
            necesita_redibujar = 0;

            if (caracter_tecla == 27) break; /* ESC */

            /* teclas especiales */
            if (caracter_tecla == 0 || caracter_tecla == 224) {

                caracter_tecla = getch();

                if (caracter_tecla == 75 && posicion_cursor > 0)
                    posicion_cursor--;

                else if (caracter_tecla == 77 && posicion_cursor < i)
                    posicion_cursor++;

                else if (caracter_tecla == 72) {

                    pos_linea = posicion_cursor;
                    while (pos_linea > 0 && contenido_buffer[pos_linea - 1] != '\n')
                        pos_linea--;

                    if (pos_linea > 0) {
                        columna = posicion_cursor - pos_linea;
                        fin_linea_prev = pos_linea - 1;

                        inicio_linea_prev = fin_linea_prev;
                        while (inicio_linea_prev > 0 && contenido_buffer[inicio_linea_prev - 1] != '\n')
                            inicio_linea_prev--;

                        if (columna <= fin_linea_prev - inicio_linea_prev)
                            posicion_cursor = inicio_linea_prev + columna;
                        else
                            posicion_cursor = fin_linea_prev + 1;
                    }

                } else if (caracter_tecla == 80) {

                    pos_linea = posicion_cursor;

                    while (pos_linea < i && contenido_buffer[pos_linea] != '\n')
                        pos_linea++;

                    if (pos_linea < i) {

                        columna = posicion_cursor;

                        inicio_linea_actual = posicion_cursor;
                        while (inicio_linea_actual > 0 && contenido_buffer[inicio_linea_actual - 1] != '\n')
                            inicio_linea_actual--;

                        columna -= inicio_linea_actual;

                        inicio_linea_sig = pos_linea + 1;

                        fin_linea_sig = inicio_linea_sig;
                        while (fin_linea_sig < i && contenido_buffer[fin_linea_sig] != '\n')
                            fin_linea_sig++;

                        if (columna <= fin_linea_sig - inicio_linea_sig)
                            posicion_cursor = inicio_linea_sig + columna;
                        else
                            posicion_cursor = fin_linea_sig;
                    }
                }

                continue;
            }

            /* backspace */
            if (caracter_tecla == 8 && posicion_cursor > 0) {
                for (j = posicion_cursor; j < i; j++)
                    contenido_buffer[j - 1] = contenido_buffer[j];
                posicion_cursor--;
                i--;
                contenido_buffer[i] = '\0';
                necesita_redibujar = 1;
            }

            /* enter */
            else if (caracter_tecla == 13) {
                if (y_cursor + alto_caracter + 6 <= limite_inf) {
                    for (j = i; j > posicion_cursor; j--)
                        contenido_buffer[j] = contenido_buffer[j - 1];
                    contenido_buffer[posicion_cursor] = '\n';
                    posicion_cursor++;
                    i++;
                    contenido_buffer[i] = '\0';
                    necesita_redibujar = 1;
                }
            }

            /* caracteres normales */
            else if (caracter_tecla >= 32 && caracter_tecla <= 126 && i < MAX_BUFFER_TEXTO - 1) {

                buffer_char[0] = caracter_tecla;
                ancho_char = textwidth(buffer_char);

                /* desborde de linea */
                if (x_cursor + ancho_char > margen_der) {

                    if (y_cursor + alto_caracter + 6 <= limite_inf) {

                        for (j = i; j > posicion_cursor; j--)
                            contenido_buffer[j] = contenido_buffer[j - 1];

                        contenido_buffer[posicion_cursor] = '\n';
                        posicion_cursor++;
                        i++;
                        contenido_buffer[i] = '\0';
                        necesita_redibujar = 1;
                    }

                } else if (y_cursor + alto_caracter <= limite_inf) {

                    for (j = i; j > posicion_cursor; j--)
                        contenido_buffer[j] = contenido_buffer[j - 1];

                    contenido_buffer[posicion_cursor] = caracter_tecla;
                    posicion_cursor++;
                    i++;
                    contenido_buffer[i] = '\0';
                    necesita_redibujar = 1;
                }
            }

            if (necesita_redibujar) {
                setfillstyle(SOLID_FILL, WHITE);
                bar(COOR_X1_AREA, COOR_Y1_AREA, COOR_X2_AREA, COOR_Y2_AREA);
                mostrarContenido(contenido_buffer);
            }
        }

        delay(20);
    }

    return COD_BTN_NINGUNO;
}

/* crear/guardar/eliminar */
void crearArchivoVacio(char nombre_arch_nuevo[]) { 
    FILE *apuntador_archivo = fopen(nombre_arch_nuevo, "w");
    if (apuntador_archivo != NULL) fclose(apuntador_archivo);
}

void guardarContenido(char nombre_arch_guardar[], char contenido_a_guardar[]) {
    FILE *apuntador_archivo = fopen(nombre_arch_guardar, "w");
    if (apuntador_archivo != NULL) {
        fputs(contenido_a_guardar, apuntador_archivo);
        fclose(apuntador_archivo);
    }
}

void mostrarContenido(char contenido_texto[]) {
    int x_actual = 10, y_actual = 70, indice;
    char buffer_char_simple[2]; buffer_char_simple[1] = '\0';
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    for (indice = 0; contenido_texto[indice] != '\0'; indice++) {
        if (contenido_texto[indice] == '\n') {
            y_actual += textheight("A") + 6;
            x_actual = 10;
        } else {
            buffer_char_simple[0] = contenido_texto[indice];
            outtextxy(x_actual, y_actual, buffer_char_simple);
            x_actual += textwidth(buffer_char_simple);
        }
    }
}

/* cargarArchivo: mensaje exacto cuando no existe */
int cargarArchivo(char nombre_archivo[]) {
    FILE *apuntador_archivo;
    int indice;
    char caracter_leido;

    apuntador_archivo = fopen(nombre_archivo, "r");
    if (!apuntador_archivo) {
        mostrarMensajeCuadro("El archivo no existe", 1500);
        return 0;
    }

    indice = 0;
    limpiarZonaEdicion();

    while ((caracter_leido = fgetc(apuntador_archivo)) != EOF && indice < MAX_BUFFER_TEXTO - 1) {
        bufferTexto[indice++] = caracter_leido;
    }
    bufferTexto[indice] = '\0';
    fclose(apuntador_archivo);

    mostrarContenido(bufferTexto);
    return 1;
}


void limpiarZonaEdicion() {
    setfillstyle(SOLID_FILL, WHITE);
    bar(COOR_X1_AREA, COOR_Y1_AREA, COOR_X2_AREA, COOR_Y2_AREA);
}

void dibujar_interfaz_app() {
    int barra1[]={0,64,639,64,639,0,0,0,0,64,128,64,128,0,256,0,256,64,383,64,383,0,511,0,511,64,639,64,0,64};
    int barra2[]={575,64,639,64,639,479,575,479,575,64,575,191,639,191,639,479,575,479,575,64};
    int pantallac[]={0,65,574,65,574,478,0,478,0,65};
    int botonnuevo[]={1,1,1,63,127,63,127,1,1,1};
    int botonguardar[]={129,1,129,63,255,63,255,1,129,1};
    int botonborrar[]={257,1,257,63,382,63,382,1,257,1};
    int botonabrir[]={384,1,384,63,510,63,510,1,384,1};
    int botonimprimir[]={512,1,512,63,638,63,638,1,512,1};
    int botonsalida[]={576,65,638,65,638,190,576,190,576,65};
    int tablerocolor[]={576,192,638,192,638,478,576,478,576,192};
    int colorr[]={584,200,631,200,631,246,584,246,584,200};
    int colorg[]={584,259,631,259,631,305,584,305,584,259};
    int colorc[]={584,322,631,322,631,368,584,368,584,366};
    int colora[]={584,384,631,384,631,430,584,430,584,384};
    int seal1[]={589,112,589,94,628,94,628,162,589,162,589,144,595,144,595,156,622,156,622,100,595,100,595,112,589,112};
    int flecha3[]={611,132,600,123,600,128,580,128,580,135,600,135,600,140,611,132};

    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillpoly(5, pantallac);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillpoly(5, barra1);
    fillpoly(5, barra2);

    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    fillpoly(5, botonnuevo);
    fillpoly(5, botonguardar);
    fillpoly(5, botonborrar);
    fillpoly(5, botonabrir);
    fillpoly(5, botonimprimir);
    fillpoly(5, botonsalida);
    fillpoly(5, tablerocolor);

    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillpoly(5, colora);

    setcolor(LIGHTRED);
    setfillstyle(SOLID_FILL, LIGHTRED);
    fillpoly(5, colorr);

    setcolor(LIGHTCYAN);
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    fillpoly(5, colorc);

    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillpoly(5, colorg);

    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    fillpoly(13, seal1);
    fillpoly(8, flecha3);

    settextstyle(1, HORIZ_DIR, 3);
    outtextxy(20,24,"Nuevo");
    outtextxy(148,24,"Guardar");
    outtextxy(272,24,"Borrar");
    outtextxy(410,24,"Abrir");

    settextstyle(1, HORIZ_DIR, 2);
    outtextxy(525, 28, "ZYRA");
}

void funcion_notas() { 
    int boton_raton, mouse_x, mouse_y;
    int modo_edicion_activo = 0; 
    int resultado_accion = COD_BTN_NINGUNO;

    cleardevice();

    dibujar_interfaz_app();
    inicializar_raton();
    mostrar_puntero_raton();

    while (1) {

        /* 1. CAPTURAR CLICKS DIRECTOS (Solo para cuando el editor NO esta activo o para establecer la accion) */
        if (!modo_edicion_activo || resultado_accion == COD_BTN_NINGUNO) {
            obtener_estado_raton(&mouse_x, &mouse_y, &boton_raton);
            if (boton_raton == 1) {
                if (mouse_x >= 1 && mouse_x <= 127 && mouse_y >= 1 && mouse_y <= 63)
                    resultado_accion = COD_BTN_NUEVO;
                else if (mouse_x >= 129 && mouse_x <= 255 && mouse_y >= 1 && mouse_y <= 63)
                    resultado_accion = COD_BTN_GUARDAR;
                else if (mouse_x >= 257 && mouse_x <= 382 && mouse_y >= 1 && mouse_y <= 63)
                    resultado_accion = COD_BTN_BORRAR;
                else if (mouse_x >= 384 && mouse_x <= 510 && mouse_y >= 1 && mouse_y <= 63)
                    resultado_accion = COD_BTN_ABRIR;
                else if (mouse_x >= 576 && mouse_x <= 638 && mouse_y >= 65 && mouse_y <= 190) {
		    ocur_raton();
                    mostrarMensajeCuadro("Saliendo...", 1000);
                    return; /* Salida inmediata por click en el boton de Salir */
                }
            }
        }

        /* 2. EDICION: Si esta activo, cede el control y capta el resultado del boton presionado */
        if (modo_edicion_activo) {
            int resultado_edicion = editarContenido(bufferTexto);

            /* Si editarContenido devuelve un codigo, sobrescribimos resultado_accion para procesarlo */
            if (resultado_edicion != COD_BTN_NINGUNO) {
                resultado_accion = resultado_edicion;
            }
        }

        /* 3. PROCESAR ACCIONES (Consolidado: se ejecuta si hay una accion pendiente) */
        if (resultado_accion != COD_BTN_NINGUNO) {

            /* NUEVO  */
            if (resultado_accion == COD_BTN_NUEVO) {
                 limpiar_buffer_teclado();
                 if (pedirNombreArchivo(nombreArchEntrada)) {
                    crearArchivoVacio(nombreArchEntrada);
                    strcpy(nombreArchActual, nombreArchEntrada);
                    bufferTexto[0] = '\0';
                    limpiarZonaEdicion();
                    mostrarContenido(bufferTexto);
                    modo_edicion_activo = 1;
                }
            }

            /*GUARDAR*/
            else if (resultado_accion == COD_BTN_GUARDAR) {
                if (nombreArchActual[0] != '\0') {
                    guardarContenido(nombreArchActual, bufferTexto);
                    mostrarMensajeCuadro("Archivo guardado!", 1000);
                }
            }

            /*BORRAR*/
            else if (resultado_accion == COD_BTN_BORRAR) {
                limpiar_buffer_teclado();
                if (pedirNombreArchivo(nombreArchEntrada)) {
                    if (eliminarArchivo(nombreArchEntrada)) {

                        limpiarZonaEdicion();
                        dibujar_interfaz_app();

                        if (strcmp(nombreArchEntrada, nombreArchActual) == 0) {
                            nombreArchActual[0] = '\0';
                            modo_edicion_activo = 0;
                        }

                        mostrarMensajeCuadro("Borrado", 1000);
                    } else {
                        mostrarMensajeCuadro("El archivo no existe", 1000);
                    }
                }
            }

            /* ABRIR */
            else if (resultado_accion == COD_BTN_ABRIR) {
                limpiar_buffer_teclado();

                if (pedirNombreArchivo(nombreArchEntrada)) {
                    if (cargarArchivo(nombreArchEntrada)) {
                        strcpy(nombreArchActual, nombreArchEntrada);
                        modo_edicion_activo = 1;
                    }
                }
            }

            /*SALIR */
            else if (resultado_accion == COD_BTN_SALIR) {
		ocur_raton();
		mover(650, 480);
                mostrarMensajeCuadro("Saliendo...", 1000);
                return; 
            }


            resultado_accion = COD_BTN_NINGUNO;
        }

        delay(20);
	}
	ocur_raton();
	return 0;
}

#endif