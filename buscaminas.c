#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

struct casilla {
	char etiqueta ;
	char tipo;
	int nMinas;
};

typedef struct casilla tipoCasilla;


/*para la funciòn que crea una matriz*/

tipoCasilla** crearMatrix(int filas, int columna){
	int i ;
	tipoCasilla** mat=(tipoCasilla**)malloc(filas*sizeof(tipoCasilla*));//numero de filas que son apuntadores a nada.
	for (i=0;i<filas; i++){
		mat[i]=(tipoCasilla*) malloc(sizeof(tipoCasilla)*columna);// espacio de memoria para las columnas
	}
	return mat; 
}

void llenarMat(tipoCasilla **mat, int filas, int columna){
	int i, j ;
	for (i =0 ; i< filas; i++){
		for(j=0 ; j<columna; j++){
			mat[i][j].etiqueta='.';
			mat[i][j].tipo='c';
			mat[i][j].nMinas=0;
		}
	}
}
 
 void dibujar(int filas,int columna, tipoCasilla** r){
	 int i,j ;
	 for (i=0 ; i<filas; i++){
		 for(j=0; j<columna; j++){
			 printf("%c %d", r[i][j].tipo, r[i][j].nMinas);
		 }
		 printf("\n");
	 }
 }

int main(int argc,char *argv[]){

    int filas=atoi(argv[1]);
    int columna=atoi(argv[2]);
    tipoCasilla ** r = crearMatrix(filas,columna);
    llenarMat(r, filas,columna);
	dibujar(filas, columna, r);
}
