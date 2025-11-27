#include <conio.h>
#include <stdio.h>
#include <graphics.h>
#include <carga.h>

int main(){
	int drive = DETECT, mode;
	initgraph(&drive, &mode, "C:\\TURBOC3\\BGI");

	carga_funcion();

	closegraph();
	return 0;
}