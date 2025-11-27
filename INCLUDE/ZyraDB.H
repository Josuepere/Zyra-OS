#ifndef ZYRADB_H
#define ZYRADB_H

/*librerias necesarias*/
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*Estructura del Empleado*/
typedef struct
{
    int id;
    char nombre[50];
    char departamento[50];
    float salario;
} Empleado;

/*Limites*/
#define MAX_EMPLEADOS 100

/*Arreglos y contadores*/
Empleado empleados[MAX_EMPLEADOS];
int contador = 0;
int id_automatico = 0;

/* prototipos de funciones */

void guardarEmpleados();
void cargarEmpleados();
void inicia_mouse();
void mostra_mouse();
void oculta_mouse();
void obtene_mouse(int *button, int *x, int *y);
void dibujar_Interfaz();
void pintarCampo(int left, int top, int right, int bottom, char *buffer);
void mostrarEnListadoTablaScroll(int inicioVisible);
void mostrarNominaScroll(int inicio);
void interfazBD();
void funcion_DB();

/*Funciones CRUD*/
/*Guardar empleados por medio de ficheros binarios*/
void guardarEmpleados()
{
    FILE *archivo;
    archivo = fopen("empleados.dat", "wb");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo para guardar.\n");
        return;
    }
    fwrite(&contador, sizeof(int), 1, archivo);
    fwrite(&id_automatico, sizeof(int), 1, archivo);
    fwrite(empleados, sizeof(Empleado), contador, archivo);
    fclose(archivo);
}

/*Mostrar los datos dentro del fichero binario*/
void cargarEmpleados()
{
    FILE *archivo;
    archivo = fopen("empleados.dat", "rb");
    if (archivo == NULL)
    {
        archivo = fopen("empleados.dat", "wb");
        if (archivo != NULL)
            fclose(archivo);
        return;
    }
    fread(&contador, sizeof(int), 1, archivo);
    fread(&id_automatico, sizeof(int), 1, archivo);
    fread(empleados, sizeof(Empleado), contador, archivo);
    fclose(archivo);
}

/*Union del mouse*/
union REGS i, o;

/*Funciones del mouse*/
void inicia_mouse()
{
    i.x.ax = 0;
    int86(0x33, &i, &o);
}
void mostra_mouse()
{
    i.x.ax = 1;
    int86(0x33, &i, &o);
}
void oculta_mouse()
{
    i.x.ax = 2;
    int86(0x33, &i, &o);
}
void obtene_mouse(int *button, int *x, int *y)
{
    i.x.ax = 3;
    int86(0x33, &i, &o);
    *button = o.x.bx;
    *x = o.x.cx;
    *y = o.x.dx;
}

/*Coordenadas y tamaños*/
#define WIN_W 640
#define WIN_H 480

#define F1_L 250
#define F1_R 520
#define F1_T 85
#define F1_B 110

#define F2_L 250
#define F2_R 520
#define F2_T 125
#define F2_B 150

#define F3_L 250
#define F3_R 520
#define F3_T 165
#define F3_B 190

#define BODY_L 20
#define BODY_R 620
#define BODY_T 220
#define BODY_B 380

#define BTN_CREAR_L 100
#define BTN_CREAR_R 230
#define BTN_CREAR_T 400
#define BTN_CREAR_B 430

#define BTN_ACT_L 250
#define BTN_ACT_R 380
#define BTN_ACT_T 400
#define BTN_ACT_B 430

/* nuevo boton Eliminar */
#define BTN_ELIM_L 390
#define BTN_ELIM_R 520
#define BTN_ELIM_T 400
#define BTN_ELIM_B 430

/* mover Salir ligeramente a la derecha para dar espacio al boton Eliminar */
#define BTN_SALIR_L 390
#define BTN_SALIR_R 520
#define BTN_SALIR_T 450
#define BTN_SALIR_B 478

#define BTN_BUSCAR_L 530
#define BTN_BUSCAR_R 600
#define BTN_BUSCAR_T F1_T
#define BTN_BUSCAR_B F1_B

#define BTN_ACEPTAR_L 530
#define BTN_ACEPTAR_R 600
#define BTN_ACEPTAR_T F3_T
#define BTN_ACEPTAR_B F3_B

/* nuevo boton Ayuda */
#define BTN_AYUDA_L 100
#define BTN_AYUDA_R 230
#define BTN_AYUDA_T 450
#define BTN_AYUDA_B 475

/* nuevo boton Nomina */
#define BTN_NOMINA_L 250
#define BTN_NOMINA_R 380
#define BTN_NOMINA_T 450
#define BTN_NOMINA_B 475

/*Funciones de dibujo*/
void dibujar_Interfaz()
{
    setfillstyle(SOLID_FILL, 15);
    bar(0, 0, WIN_W, WIN_H);

    setcolor(BLACK);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
    outtextxy(40, 40, "Datos del Empleado");

    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    outtextxy(40, 90, "Nombre del empleado:");
    outtextxy(40, 130, "Departamento:");
    outtextxy(40, 170, "Salario:");

    setfillstyle(SOLID_FILL, 7);
    bar(F1_L, F1_T, F1_R, F1_B);
    rectangle(F1_L, F1_T, F1_R, F1_B);

    bar(F2_L, F2_T, F2_R, F2_B);
    rectangle(F2_L, F2_T, F2_R, F2_B);

    bar(F3_L, F3_T, F3_R, F3_B);
    rectangle(F3_L, F3_T, F3_R, F3_B);

    setcolor(DARKGRAY);
    line(20, 210, 620, 210);
    rectangle(BODY_L, BODY_T, BODY_R, BODY_B);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
    outtextxy(260, 225, "Listado de empleados");

    /*Boton Crear*/
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, 7);
    bar(BTN_CREAR_L, BTN_CREAR_T, BTN_CREAR_R, BTN_CREAR_B);
    rectangle(BTN_CREAR_L, BTN_CREAR_T, BTN_CREAR_R, BTN_CREAR_B);
    outtextxy(BTN_CREAR_L + 40, BTN_CREAR_T + 5, "Crear");

    /*Boton Actualizar*/
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, 7);
    bar(BTN_ACT_L, BTN_ACT_T, BTN_ACT_R, BTN_ACT_B);
    rectangle(BTN_ACT_L, BTN_ACT_T, BTN_ACT_R, BTN_ACT_B);
    outtextxy(BTN_ACT_L + 25, BTN_ACT_T + 5, "Actualizar");

    /*Boton Eliminar (nuevo)*/
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, 7);
    bar(BTN_ELIM_L, BTN_ELIM_T, BTN_ELIM_R, BTN_ELIM_B);
    rectangle(BTN_ELIM_L, BTN_ELIM_T, BTN_ELIM_R, BTN_ELIM_B);
    outtextxy(BTN_ELIM_L + 35, BTN_ELIM_T + 5, "Eliminar");

    /*Boton Ayuda*/
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, 7);
    bar(BTN_AYUDA_L, BTN_AYUDA_T, BTN_AYUDA_R, BTN_AYUDA_B);
    rectangle(BTN_AYUDA_L, BTN_AYUDA_T, BTN_AYUDA_R, BTN_AYUDA_B);
    outtextxy((BTN_AYUDA_L + BTN_AYUDA_R) / 2 - 25, (BTN_AYUDA_T + BTN_AYUDA_B) / 2 - 5, "Ayuda");

    /*Boton Nomina*/
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, 7);
    bar(BTN_NOMINA_L, BTN_NOMINA_T, BTN_NOMINA_R, BTN_NOMINA_B);
    rectangle(BTN_NOMINA_L, BTN_NOMINA_T, BTN_NOMINA_R, BTN_NOMINA_B);
    outtextxy((BTN_NOMINA_L + BTN_NOMINA_R) / 2 - 25, (BTN_NOMINA_T + BTN_NOMINA_B) / 2 - 5, "Nomina");

    /*Boton Salir*/
    setfillstyle(SOLID_FILL, 4);
    bar(BTN_SALIR_L, BTN_SALIR_T, BTN_SALIR_R, BTN_SALIR_B);
    setcolor(WHITE);
    rectangle(BTN_SALIR_L, BTN_SALIR_T, BTN_SALIR_R, BTN_SALIR_B);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
    outtextxy(BTN_SALIR_L + 30, BTN_SALIR_T + 8, "SALIR");
}

/*Campo de texto*/
void pintarCampo(int left, int top, int right, int bottom, char *buffer)
{
    int start_x, start_y, alto;
    start_x = left + 5;
    start_y = top + 5;
    alto = textheight("A");
    setfillstyle(SOLID_FILL, 7);
    bar(left + 1, top + 1, right - 1, bottom - 1);
    setcolor(BLACK);
    outtextxy(start_x, start_y, buffer);
    rectangle(left, top, right, bottom);
}

/*Listado con scroll*/
int filasVisibles = 5;
int filasNomina = 13;

void mostrarEnListadoTablaScroll(int inicioVisible)
{
    int i;
    int startX = BODY_L + 5;
    int startY = BODY_T + 30;
    int col_id = startX + 10;
    int col_nombre = startX + 60;
    int col_depart = startX + 240;
    int col_salario = startX + 430;
    int row_height = 20;

    setfillstyle(SOLID_FILL, 15);
    bar(BODY_L + 1, BODY_T + 1, BODY_R - 1, BODY_B - 1);
    setcolor(BLACK);

    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    outtextxy(col_id, startY - 8, "ID");
    outtextxy(col_nombre, startY - 8, "Nombre");
    outtextxy(col_depart, startY - 8, "Departamento");
    outtextxy(col_salario, startY - 8, "Salario");

    line(BODY_L + 1, startY + 15, BODY_R - 1, startY + 15);

    for (i = 0; i < filasVisibles; i++)
    {
        int idx = inicioVisible + i;
        char bufferID[10], bufferSalario[20];

        if (idx >= contador)
            break;

        sprintf(bufferID, "%d", empleados[idx].id);
        sprintf(bufferSalario, "%.2f", empleados[idx].salario);

        outtextxy(col_id, startY + 20 + (i * row_height), bufferID);
        outtextxy(col_nombre, startY + 20 + (i * row_height), empleados[idx].nombre);
        outtextxy(col_depart, startY + 20 + (i * row_height), empleados[idx].departamento);
        outtextxy(col_salario, startY + 20 + (i * row_height), bufferSalario);
    }

    line(col_id - 5, BODY_T, col_id - 5, BODY_B);
    line(col_nombre - 5, BODY_T, col_nombre - 5, BODY_B);
    line(col_depart - 5, BODY_T, col_depart - 5, BODY_B);
    line(col_salario - 5, BODY_T, col_salario - 5, BODY_B);
}

#define FILA_ALTURA 25

void mostrarNominaScroll(int inicio)
{
	/*int filasVisibles = 12;*/
    int box_left = 10, box_top = 10, box_right = WIN_W - 10, box_bottom = WIN_H - 10;
    int startY = box_top + 40;
    int filasMax = filasNomina;
    int i;
    int row_y;
    char tmp[60];
    float isr, neto;

    /* DIBUJO FIJO (NO CAMBIA) */
    setfillstyle(SOLID_FILL, WHITE);
    bar(0, 0, WIN_W, WIN_H);

    setcolor(BLACK);
    rectangle(box_left, box_top, box_right, box_bottom);

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
    outtextxy((WIN_W / 2) - 120, box_top + 10, "INFORME DE NOMINA");

    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
    outtextxy(box_left + 15, startY, "ID");
    outtextxy(box_left + 70, startY, "Nombre");
    outtextxy(box_left + 235, startY, "Departamento");
    outtextxy(box_left + 375, startY, "Salario");
    outtextxy(box_left + 465, startY, "ISR");
    outtextxy(box_left + 545, startY, "Neto");

    line(box_left + 10, startY + 20, box_right - 10, startY + 20);

    outtextxy(box_left + 20, box_bottom - 30, "Flechas para desplazarse. ESC para volver.");

    /* LIMPIAR SOLO ZONA DE FILAS (EVITA PARPADEO) */
    setfillstyle(SOLID_FILL, WHITE);
    bar(box_left + 5, startY + 25, box_right - 5, box_bottom - 40);

    /* DIBUJAR FILAS */
    row_y = startY + 35;

    for (i = inicio; i < inicio + filasMax && i < contador; i++)
    {
        isr = empleados[i].salario * 0.10;
        neto = empleados[i].salario - isr;

        sprintf(tmp, "%d", empleados[i].id);
        outtextxy(box_left + 12, row_y, tmp);

        outtextxy(box_left + 62, row_y, empleados[i].nombre);
        outtextxy(box_left + 232, row_y, empleados[i].departamento);

        sprintf(tmp, "%.2f", empleados[i].salario);
        outtextxy(box_left + 372, row_y, tmp);

        sprintf(tmp, "%.2f", isr);
        outtextxy(box_left + 462, row_y, tmp);

        sprintf(tmp, "%.2f", neto);
        outtextxy(box_left + 542, row_y, tmp);

        row_y += FILA_ALTURA;
    }
}

/*Interfaz principal con logica*/
void interfazBD()
{
    int button = 0, mx = 0, my = 0;
    int i0 = 0, i1 = 0, i2 = 0;
    int campoActivo = 0;
    int alto = 0;
    char c = 0;
    char temp[2];
    char nombre[60], dept[60], salario[30];
    int salir = 0;
    int inicioVisible = 0;

    /* Variables para actualizar */
    int modoActualizar = 0;
    char idbuf[12];
    int id_i = 0;
    int encontradoIdx = -1;
    char mensaje[80];
    int mostrarMensaje = 0;

    /* Variables para eliminar */
    int modoEliminar = 0;
    char idbuf_el[12];
    int id_i_el = 0;
    int encontradoIdxEl = -1;

    strcpy(nombre, "");
    strcpy(dept, "");
    strcpy(salario, "");
    strcpy(idbuf, "");
    strcpy(idbuf_el, "");
    strcpy(mensaje, "");

    dibujar_Interfaz();
    mostrarEnListadoTablaScroll(inicioVisible);
    inicia_mouse();
    mostra_mouse();

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
    alto = textheight("A");

    while (!salir)
    {
        obtene_mouse(&button, &mx, &my);

        if ((button & 1))
        {
            /* Click en cajas de texto */
            if (mx >= F1_L && mx <= F1_R && my >= F1_T && my <= F1_B)
            {
                campoActivo = 1;
            }
            else if (mx >= F2_L && mx <= F2_R && my >= F2_T && my <= F2_B)
            {
                /* solo permitir activar F2 si no estamos en modo 1 (ingresar ID) */
                if (modoActualizar != 1 && modoEliminar != 1)
                    campoActivo = 2;
                else
                    campoActivo = 0;
            }
            else if (mx >= F3_L && mx <= F3_R && my >= F3_T && my <= F3_B)
            {
                if (modoActualizar != 1 && modoEliminar != 1)
                    campoActivo = 3;
                else
                    campoActivo = 0;
            }

            /* BOTON CREAR (solo en modo normal) */
            /* BOTON CREAR */
            else if (mx >= BTN_CREAR_L && mx <= BTN_CREAR_R && my >= BTN_CREAR_T && my <= BTN_CREAR_B)
            {
                /* Si estamos en modo actualizar o eliminar → redirigir a vista principal */
                if (modoActualizar != 0 || modoEliminar != 0)
                {
                    modoActualizar = 0;
                    modoEliminar = 0;
                    campoActivo = 0;
                    strcpy(nombre, "");
                    strcpy(dept, "");
                    strcpy(salario, "");
                    i0 = i1 = i2 = 0;

                    /* Redibujar interfaz principal limpia */
                    dibujar_Interfaz();
                    if (contador > filasVisibles)
                        inicioVisible = contador - filasVisibles;
                    else
                        inicioVisible = 0;
                    mostrarEnListadoTablaScroll(inicioVisible);
                }
                /* Si estamos en modo normal crear nuevo empleado */
                else
                {
                    if (strlen(nombre) > 0 && strlen(dept) > 0 && strlen(salario) > 0)
                    {
                        Empleado nuevo;
                        nuevo.id = id_automatico++;
                        strcpy(nuevo.nombre, nombre);
                        strcpy(nuevo.departamento, dept);
                        nuevo.salario = atof(salario);
                        empleados[contador++] = nuevo;
                        guardarEmpleados();

                        if (contador > filasVisibles)
                            inicioVisible = contador - filasVisibles;
                        else
                            inicioVisible = 0;

                        mostrarEnListadoTablaScroll(inicioVisible);

                        strcpy(nombre, "");
                        strcpy(dept, "");
                        strcpy(salario, "");
                        i0 = i1 = i2 = 0;
                        pintarCampo(F1_L, F1_T, F1_R, F1_B, nombre);
                        pintarCampo(F2_L, F2_T, F2_R, F2_B, dept);
                        pintarCampo(F3_L, F3_T, F3_R, F3_B, salario);
                    }
                }
            }

            /* BOTON ACTUALIZAR: pasar a modo ingresar ID */
            else if (mx >= BTN_ACT_L && mx <= BTN_ACT_R && my >= BTN_ACT_T && my <= BTN_ACT_B)
            {
                modoActualizar = 1;
                modoEliminar = 0;
                campoActivo = 1;
                id_i = 0;
                strcpy(idbuf, "");
                mostrarMensaje = 0;
                encontradoIdx = -1;

                /* Limpiar encabezado (mas amplio para eliminar etiquetas antiguas) */
                setfillstyle(SOLID_FILL, 15);
                bar(20, 70, 620, 200);

                /* Redibujar titulo y etiqueta ID */
                setcolor(BLACK);
                settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
                outtextxy(40, 40, "Datos del Empleado");

                settextstyle(SMALL_FONT, HORIZ_DIR, 6);
                outtextxy(70, 85, "ID del empleado:");

                /* Dibujar campo ID (usa la misma funcion pintarCampo para consistencia) */
                pintarCampo(F1_L, F1_T, F1_R - 60, F1_B, idbuf);

                /* Redibujar cuadro de la tabla completo (restaurar borde si se borro) */
                setcolor(DARKGRAY);
                line(20, 210, 620, 210);
                rectangle(BODY_L, BODY_T, BODY_R, BODY_B);
                settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
                /*outtextxy(260, 225, "Listado de empleados");*/
                mostrarEnListadoTablaScroll(inicioVisible);
            }

            /* BOTON ELIMINAR: pasar a modo ingresar ID para eliminar */
            else if (mx >= BTN_ELIM_L && mx <= BTN_ELIM_R && my >= BTN_ELIM_T && my <= BTN_ELIM_B)
            {
                modoEliminar = 1;
                modoActualizar = 0;
                campoActivo = 1;
                id_i_el = 0;
                strcpy(idbuf_el, "");
                mostrarMensaje = 0;
                encontradoIdxEl = -1;

                /* Limpiar encabezado */
                setfillstyle(SOLID_FILL, 15);
                bar(20, 70, 620, 200);

                /* Redibujar titulo y etiqueta ID */
                setcolor(BLACK);
                settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
                outtextxy(40, 40, "Datos del Empleado");

                settextstyle(SMALL_FONT, HORIZ_DIR, 6);
                outtextxy(70, 75, "ID del empleado");
                outtextxy(70, 95, "a eliminar:");

                /* Dibujar campo ID (usa la misma funcion pintarCampo para consistencia) */
                pintarCampo(F1_L, F1_T, F1_R - 60, F1_B, idbuf_el);

                /* Redibujar cuadro de la tabla completo */
                setcolor(DARKGRAY);
                line(20, 210, 620, 210);
                rectangle(BODY_L, BODY_T, BODY_R, BODY_B);
                settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
                mostrarEnListadoTablaScroll(inicioVisible);

            }

            /* BOTON BUSCAR (click sobre el boton) - también se ejecuta al presionar Enter en ID */
            else if (mx >= (F1_R - 55) && mx <= F1_R && my >= F1_T && my <= F1_B && modoActualizar == 1)
            {
                int idBuscar = atoi(idbuf);
                int j;
                encontradoIdx = -1;
                for (j = 0; j < contador; j++)
                {
                    if (empleados[j].id == idBuscar)
                    {
                        encontradoIdx = j;
                        break;
                    }
                }
                if (encontradoIdx == -1)
                {
                    mostrarMensaje = 1;
                    strcpy(mensaje, "Empleado no encontrado");

                    /* Redibujar el area del encabezado y mostrar mensaje */
                    setfillstyle(SOLID_FILL, 15);
                    bar(20, 70, 620, 200);
                    setcolor(BLACK);
                    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
                    outtextxy(40, 40, "Datos del Empleado");
                    settextstyle(SMALL_FONT, HORIZ_DIR, 6);
                    outtextxy(40, 90, "ID del empleado:");
                    pintarCampo(F1_L, F1_T, F1_R - 60, F1_B, idbuf);
                    setcolor(RED);
                    outtextxy(F1_L, F1_B + 10, mensaje);
                    /* volver a dibujar boton Buscar */
                    setfillstyle(SOLID_FILL, 7);
                    bar(F1_R - 55, F1_T, F1_R, F1_B);
                    rectangle(F1_R - 55, F1_T, F1_R, F1_B);
                    setcolor(BLACK);
                    outtextxy(F1_R - 45, F1_T + 5, "Buscar");

                    /* restaurar tabla */
                    setcolor(DARKGRAY);
                    line(20, 210, 620, 210);
                    rectangle(BODY_L, BODY_T, BODY_R, BODY_B);
                    mostrarEnListadoTablaScroll(inicioVisible);
                }
                else
                {
                    /* Pasar a modo edicion y rellenar campos con los datos encontrados */
                    modoActualizar = 2;
                    strcpy(nombre, empleados[encontradoIdx].nombre);
                    strcpy(dept, empleados[encontradoIdx].departamento);
                    sprintf(salario, "%.2f", empleados[encontradoIdx].salario);
                    i0 = strlen(nombre);
                    i1 = strlen(dept);
                    i2 = strlen(salario);

                    /* Redibujar interfaz normal con campos llenos y boton Aceptar */
                    dibujarInterfaz();
                    mostrarEnListadoTablaScroll(inicioVisible);
                    pintarCampo(F1_L, F1_T, F1_R, F1_B, nombre);
                    pintarCampo(F2_L, F2_T, F2_R, F2_B, dept);
                    pintarCampo(F3_L, F3_T, F3_R, F3_B, salario);

                    setfillstyle(SOLID_FILL, 7);
                    bar(BTN_ACEPTAR_L, BTN_ACEPTAR_T, BTN_ACEPTAR_R, BTN_ACEPTAR_B);
                    rectangle(BTN_ACEPTAR_L, BTN_ACEPTAR_T, BTN_ACEPTAR_R, BTN_ACEPTAR_B);
                    setcolor(BLACK);
                    outtextxy(BTN_ACEPTAR_L + 10, BTN_ACEPTAR_T + 5, "Aceptar");

                    campoActivo = 1; /* poner foco en nombre (como en crear) */
                }
            }

            /* BOTON ACEPTAR (guardar cambios o confirmar eliminacion) */
            else if (mx >= BTN_ACEPTAR_L && mx <= BTN_ACEPTAR_R && my >= BTN_ACEPTAR_T && my <= BTN_ACEPTAR_B && (modoActualizar == 2 || modoEliminar == 1))
            {
                if (modoEliminar == 1)
                {
                    int idEliminar = atoi(idbuf_el);
                    int i, indice = -1;
                    for (i = 0; i < contador; i++)
                    {
                        if (empleados[i].id == idEliminar)
                        {
                            indice = i;
                            break;
                        }
                    }
                    if (indice != -1)
                    {
                        /* desplazar elementos hacia la izquierda */
                        for (i = indice; i < contador - 1; i++)
                        {
                            empleados[i] = empleados[i + 1];
                        }
                        contador--;
                        if (contador == 0)
                        {
                            id_automatico = 0;
                        }
                        guardarEmpleados();

                        modoEliminar = 0;
                        campoActivo = 0;

                        /* redibujar interfaz principal y listado actualizado */
                        dibujar_Interfaz();
                        if (contador > filasVisibles)
                            inicioVisible = contador - filasVisibles;
                        else
                            inicioVisible = 0;
                        mostrarEnListadoTablaScroll(inicioVisible);
                    }
                    else
                    {
                        /* empleado no encontrado */
                        setfillstyle(SOLID_FILL, 15);
                        bar(20, 70, 620, 200);
                        setcolor(BLACK);
                        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
                        outtextxy(40, 40, "Datos del Empleado");
                        settextstyle(SMALL_FONT, HORIZ_DIR, 6);
                        outtextxy(40, 90, "ID del empleado a eliminar:");
                        pintarCampo(F1_L, F1_T, F1_R - 60, F1_B, idbuf_el);
                        setcolor(RED);
                        outtextxy(F1_L, F1_B + 10, "Empleado no encontrado");

                        /* restaurar tabla */
                        setcolor(DARKGRAY);
                        line(20, 210, 620, 210);
                        rectangle(BODY_L, BODY_T, BODY_R, BODY_B);
                        mostrarEnListadoTablaScroll(inicioVisible);
                    }
                }
                else if (modoActualizar == 2)
                {
                    if (encontradoIdx != -1)
                    {
                        strcpy(empleados[encontradoIdx].nombre, nombre);
                        strcpy(empleados[encontradoIdx].departamento, dept);
                        empleados[encontradoIdx].salario = atof(salario);
                        guardarEmpleados();

                        /* volver a modo normal */
                        modoActualizar = 0;
                        encontradoIdx = -1;
                        strcpy(nombre, "");
                        strcpy(dept, "");
                        strcpy(salario, "");
                        i0 = i1 = i2 = 0;

                        /* limpiar completamente el area superior */
                        setfillstyle(SOLID_FILL, 15);
                        bar(20, 40, 620, 200);

                        /* redibujar interfaz principal */
                        dibujar_Interfaz();
                        if (contador > filasVisibles)
                            inicioVisible = contador - filasVisibles;
                        else
                            inicioVisible = 0;
                        mostrarEnListadoTablaScroll(inicioVisible);

                        oculta_mouse();
                        setfillstyle(SOLID_FILL, 15);
                        bar(mx - 15, my - 15, mx + 15, my + 15);
                        mostra_mouse();

                        /* SIN mostrar mensaje */
                    }
                }
            }

            /* BOTON AYUDA */
            else if (mx >= BTN_AYUDA_L && mx <= BTN_AYUDA_R && my >= BTN_AYUDA_T && my <= BTN_AYUDA_B)
            {
                int btn = 0;
                int x = 0;
                int y = 0;

                setfillstyle(SOLID_FILL, 15);
                bar(0, 0, WIN_W, WIN_H);

                setcolor(BLACK);
                settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
                outtextxy(50, 50, "AYUDA");

                settextstyle(SMALL_FONT, HORIZ_DIR, 5);
                outtextxy(50, 100, "Guia Base de Datos:");
                outtextxy(50, 120, "CREAR");
                outtextxy(50, 140, "1. Ingrese los datos del empleado: Nombre del Empleado, Departamento");
                outtextxy(50, 160, "Y salario del empleado. Click en el boton CREAR para guardar.");
                outtextxy(50, 180, "ACTUALIZAR");
                outtextxy(50, 200, "2. Actualizar: Recibe de parametro escencial el ID del empleado a modificar.");
                outtextxy(50, 220, "Luego permite modificar los datos y guardar los cambios.");
                outtextxy(50, 240, "ELIMINAR");
                outtextxy(50, 260, "3. Eliminar: Recibe de parametro el ID del empleado a eliminar.");
                outtextxy(50, 280, "NOMINA");
                outtextxy(50, 300, "4. Muestra un informe de nomina con calculos de ISR y salario neto.");

                outtextxy(50, 400, "Presione ESC para volver.");

                /* Bucle permanente hasta que presione ESC o click */
                while (1)
                {
                    if (kbhit())
                    {
                        char c = getch();
                        if (c == 27)
                            break;
                    }
                    delay(20);
                }

                dibujar_Interfaz();
                if (contador > filasVisibles)
                    inicioVisible = contador - filasVisibles;
                else
                    inicioVisible = 0;
                mostrarEnListadoTablaScroll(inicioVisible);
            }

            /* BOTON NOMINA */
            else if (mx >= BTN_NOMINA_L && mx <= BTN_NOMINA_R && my >= BTN_NOMINA_T && my <= BTN_NOMINA_B)
            {
                int tecla;

                inicioVisible = 0;

                mostrarNominaScroll(inicioVisible);

                /* Control del scroll */
                while (1)
                {
                    if (kbhit())
                    {
                        tecla = getch();

                        if (tecla == 27) /* ESC para salir */
                            break;

                        /* Flecha arriba */
                        if (tecla == 72 && inicioVisible > 0)
                        {
                            inicioVisible--;
                            mostrarNominaScroll(inicioVisible);
                        }

                        /* Flecha abajo */
                        if (tecla == 80 && inicioVisible + filasNomina < contador)
                        {
                            inicioVisible++;
                            mostrarNominaScroll(inicioVisible);
                        }
                    }

                    delay(15); /* Animación más suave */
                }

                /* Volver */
                dibujar_Interfaz();
                mostrarEnListadoTablaScroll(inicioVisible);
            }

            /* BOTON SALIR */
            else if (mx >= BTN_SALIR_L && mx <= BTN_SALIR_R && my >= BTN_SALIR_T && my <= BTN_SALIR_B)
            {
                salir = 1;
            }
        }

        /*teclado*/
        if (kbhit())
        {
            c = getch();

            /* detectar flechas: mantener scroll activo en cualquier modo */
            if (c == 0 || c == 224)
            {
                c = getch();
                if (c == 80 && inicioVisible + filasVisibles < contador)
                { /* flecha abajo */
                    inicioVisible++;
                    mostrarEnListadoTablaScroll(inicioVisible);
                }
                else if (c == 72 && inicioVisible > 0)
                { /* flecha arriba */
                    inicioVisible--;
                    mostrarEnListadoTablaScroll(inicioVisible);
                }
            }
            else
            {
                if ((modoActualizar == 1 && campoActivo == 1) || (modoEliminar == 1 && campoActivo == 1))
                {
                    /* caso modo actualizar: trabajar sobre idbuf
                       caso modo eliminar: trabajar sobre idbuf_el */
                    if ((modoActualizar == 1 && campoActivo == 1 && c == 13) || (modoEliminar == 1 && campoActivo == 1 && c == 13))
                    {
                        if (modoActualizar == 1)
                        {
                            /* Enter actua como Buscar en actualizar */
                            int idBuscar = atoi(idbuf);
                            int j;
                            encontradoIdx = -1;
                            for (j = 0; j < contador; j++)
                            {
                                if (empleados[j].id == idBuscar)
                                {
                                    encontradoIdx = j;
                                    break;
                                }
                            }
                            if (encontradoIdx == -1)
                            {
                                mostrarMensaje = 1;
                                strcpy(mensaje, "Empleado no encontrado");
                                setfillstyle(SOLID_FILL, 15);
                                bar(20, 70, 620, 200);
                                setcolor(BLACK);
                                settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
                                outtextxy(40, 40, "Datos del Empleado");
                                settextstyle(SMALL_FONT, HORIZ_DIR, 6);
                                outtextxy(40, 90, "ID del empleado:");
                                pintarCampo(F1_L, F1_T, F1_R - 60, F1_B, idbuf);
                                setcolor(RED);
                                outtextxy(F1_L, F1_B + 10, mensaje);
                                setfillstyle(SOLID_FILL, 7);
                                bar(F1_R - 55, F1_T, F1_R, F1_B);
                                rectangle(F1_R - 55, F1_T, F1_R, F1_B);
                                setcolor(BLACK);
                                outtextxy(F1_R - 45, F1_T + 5, "Buscar");
                                setcolor(DARKGRAY);
                                line(20, 210, 620, 210);
                                rectangle(BODY_L, BODY_T, BODY_R, BODY_B);
                                mostrarEnListadoTablaScroll(inicioVisible);
                            }
                            else
                            {
                                modoActualizar = 2;
                                strcpy(nombre, empleados[encontradoIdx].nombre);
                                strcpy(dept, empleados[encontradoIdx].departamento);
                                sprintf(salario, "%.2f", empleados[encontradoIdx].salario);
                                i0 = strlen(nombre);
                                i1 = strlen(dept);
                                i2 = strlen(salario);
                                dibujar_Interfaz();
                                mostrarEnListadoTablaScroll(inicioVisible);
                                pintarCampo(F1_L, F1_T, F1_R, F1_B, nombre);
                                pintarCampo(F2_L, F2_T, F2_R, F2_B, dept);
                                pintarCampo(F3_L, F3_T, F3_R, F3_B, salario);
                                setfillstyle(SOLID_FILL, 7);
                                bar(BTN_ACEPTAR_L, BTN_ACEPTAR_T, BTN_ACEPTAR_R, BTN_ACEPTAR_B);
                                rectangle(BTN_ACEPTAR_L, BTN_ACEPTAR_T, BTN_ACEPTAR_R, BTN_ACEPTAR_B);
                                outtextxy(BTN_ACEPTAR_L + 10, BTN_ACEPTAR_T + 5, "Aceptar");
                                campoActivo = 1;
                            }
                        }
                        else if (modoEliminar == 1)
                        {
                            /* Enter confirma eliminacion */
                            int idEliminar = atoi(idbuf_el);
                            int i, indice = -1;
                            for (i = 0; i < contador; i++)
                            {
                                if (empleados[i].id == idEliminar)
                                {
                                    indice = i;
                                    break;
                                }
                            }
                            if (indice != -1)
                            {
                                for (i = indice; i < contador - 1; i++)
                                {
                                    empleados[i] = empleados[i + 1];
                                }
                                contador--;
                                if (contador == 0)
                                {
                                    id_automatico = 0;
                                }
                                guardarEmpleados();

                                setfillstyle(SOLID_FILL, 15);
                                bar(20, 70, 620, 200);
                                setcolor(BLACK);
                                settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
                                outtextxy(40, 40, "Datos del Empleado");
                                strcpy(mensaje, "Empleado eliminado correctamente.");
                                setcolor(GREEN);
                                outtextxy(F1_L, F1_B + 10, mensaje);

                                modoEliminar = 0;
                                campoActivo = 0;

                                dibujar_Interfaz();
                                if (contador > filasVisibles)
                                    inicioVisible = contador - filasVisibles;
                                else
                                    inicioVisible = 0;
                                mostrarEnListadoTablaScroll(inicioVisible);
                            }
                            else
                            {
                                setfillstyle(SOLID_FILL, 15);
                                bar(20, 70, 620, 200);
                                setcolor(BLACK);
                                settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
                                outtextxy(40, 40, "Datos del Empleado");
                                settextstyle(SMALL_FONT, HORIZ_DIR, 6);
                                outtextxy(40, 90, "ID del empleado a eliminar:");
                                pintarCampo(F1_L, F1_T, F1_R - 60, F1_B, idbuf_el);
                                setcolor(RED);
                                outtextxy(F1_L, F1_B + 10, "Empleado no encontrado");
                                setcolor(DARKGRAY);
                                line(20, 210, 620, 210);
                                rectangle(BODY_L, BODY_T, BODY_R, BODY_B);
                                mostrarEnListadoTablaScroll(inicioVisible);
                            }
                        }
                    }
                    else if (c == 8)
                    {
                        if (modoActualizar == 1 && id_i > 0)
                        {
                            id_i--;
                            idbuf[id_i] = '\0';
                            pintarCampo(F1_L, F1_T, F1_R - 60, F1_B, idbuf);
                        }
                        else if (modoEliminar == 1 && id_i_el > 0)
                        {
                            id_i_el--;
                            idbuf_el[id_i_el] = '\0';
                            pintarCampo(F1_L, F1_T, F1_R - 60, F1_B, idbuf_el);
                        }
                    }
                    else if (c >= '0' && c <= '9')
                    {
                        if (modoActualizar == 1 && id_i < 10)
                        {
                            idbuf[id_i++] = c;
                            idbuf[id_i] = '\0';
                            pintarCampo(F1_L, F1_T, F1_R - 60, F1_B, idbuf);
                        }
                        else if (modoEliminar == 1 && id_i_el < 10)
                        {
                            idbuf_el[id_i_el++] = c;
                            idbuf_el[id_i_el] = '\0';
                            pintarCampo(F1_L, F1_T, F1_R - 60, F1_B, idbuf_el);
                        }
                    }
                }
                else
                {
                    /* comportamiento de los inputs normales (crear / editar) */
                    if (campoActivo != 0)
                    {
                        if (c == 13)
                            campoActivo++;
                        else if (c == 8)
                        {
                            if (campoActivo == 1 && i0 > 0)
                            {
                                i0--;
                                nombre[i0] = '\0';
                                pintarCampo(F1_L, F1_T, F1_R, F1_B, nombre);
                            }
                            else if (campoActivo == 2 && i1 > 0)
                            {
                                i1--;
                                dept[i1] = '\0';
                                pintarCampo(F2_L, F2_T, F2_R, F2_B, dept);
                            }
                            else if (campoActivo == 3 && i2 > 0)
                            {
                                i2--;
                                salario[i2] = '\0';
                                pintarCampo(F3_L, F3_T, F3_R, F3_B, salario);
                            }
                        }
                        else if (c >= 32 && c <= 126)
                        {
                            temp[0] = c;
                            temp[1] = '\0';
                            if (campoActivo == 1 && i0 < 59)
                            {
                                nombre[i0++] = c;
                                nombre[i0] = '\0';
                                pintarCampo(F1_L, F1_T, F1_R, F1_B, nombre);
                            }
                            else if (campoActivo == 2 && i1 < 59)
                            {
                                dept[i1++] = c;
                                dept[i1] = '\0';
                                pintarCampo(F2_L, F2_T, F2_R, F2_B, dept);
                            }
                            else if (campoActivo == 3 && i2 < 29)
                            {
                                salario[i2++] = c;
                                salario[i2] = '\0';
                                pintarCampo(F3_L, F3_T, F3_R, F3_B, salario);
                            }
                        }
                    }
                }
            }
        }

        delay(40);
    }

    oculta_mouse();
    return;
}

void mostrarMensajesLinux()
{
    int i;

    printf("Iniciando ZyraDB...\n");
    delay(500);

    printf("Leyendo modulos del sistema...\n");
    delay(400);

    printf("Comprobando dependencias...\n");
    delay(500);

    for(i = 1; i <= 10; i++)
    {
        printf("Instalando dependencia (%d/10): libzyra%d... [OK]\n", i, i);
        delay(250);
    }

    delay(300);

    printf("Leyendo listas de paquetes...\n");
    delay(500);

    printf("Construyendo arbol de dependencias...\n");
    delay(500);

    printf("Leyendo informacion del estado...\n");
    delay(500);

    for(i = 1; i <= 8; i++)
    {
        printf("Configurando paquete zyra-utils-%d (1.%d.0) ...\n", i, i);
        delay(350);
    }

    delay(400);

    printf("Cargando controladores graficos...\n");
    delay(600);

    printf("Inicializando servicios de red...\n");
    delay(600);

    printf("Montando base de datos ZyraDB...\n");
    delay(700);

    printf("Procesando disparadores del sistema...\n");
    delay(600);

    printf("Optimizando cache...\n");
    delay(500);

    printf("Limpieza de procesos temporales...\n");
    delay(400);

    printf("\nBIENVENIDO.\n");
    delay(2000);
}


/*Terminal tipo Linux*/
void funcion_DB()
{
    int gdriver, gmode;
    int estado = 0;
    char comando[50];

    while (estado == 0)
    {
        clrscr();
        printf("root@ZyraDB:~$ ");
        scanf("%s", comando);

        if (strcmp(comando, "xdg-open") == 0)
        {
            scanf("%s", comando);
            if (strcmp(comando, "ZyraDB") == 0)
            {
                mostrarMensajesLinux();
                cargarEmpleados();
                estado = 1;
                gdriver = DETECT;
                initgraph(&gdriver, &gmode, "C:\\TC20\\BIN");
                interfazBD();
            }
            else
            {
                printf("Error: base de datos '%s' no encontrada.\n", comando);
                getch();
            }
        }
        else if (strcmp(comando, "exit") == 0)
        {
            printf("Cerrando ZyraDB Terminal...\n");
            estado = 1;
        }
        else
        {
            printf("Comando no reconocido.\n");
            getch();
        }
    }
    return;
}

#endif