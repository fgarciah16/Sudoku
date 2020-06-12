
// Declaracion de variables 
#include <conio.h>
#include <dos.h>
#include <stdio.h>
# define VIDEO 0x10

// Estructura de los elementos agrupados
struct disco{
	int StructSize;
	int Level;
	long SectorsPerCluster;
	long BytesPerSector;
	long AvailableClusters;
	long TotalClusters;
	long AvailablePhysSectors;
	long TotalPhysSectors;
	long AvailableAllocationUnits;
	long TotalAllocationUnits;
	char Rsvd[64];
} bufer;


// Definicion de variables 
long vol;
int tam=352;
char nombreUnidad[] = "C";
char nombreruta[]="discos $";
char err[]="no se realizo la accion$";
char nombrearchivo[]="trabajo4.txt$";
char nombrerutad[10];


//Metodo el cual indica el volumen 
int Volumen(void){
	bufer.Level=0;
	asm{
		mov di, OFFSET bufer // Direccion
		mov cx,tam  // Instruccion para el tamaño del bufer
		mov dx,OFFSET nombreUnidad // nombre que se le dara 
		mov ax,7303h  // instruccion para tener espacio en el disco
		int 21h	}

	vol = (bufer.SectorsPerCluster * 512 * bufer.TotalClusters) / 1024;
	return vol;
    
}

// Metodo para crear el directorio
void crearsub(void){

	asm{
		mov ah,39h // Se crea un nuevo directorio usando la unidad de disco
		mov dx,OFFSET nombreruta // Nombre de la ruta del directorio a imprimir
		int 21h //Instruccion de interrupcion 
		jc errord	// salto	
        }
		printf(" Subdirectorio creado"); // Mensaje del directorio creado
		asm jmp salir //salto
		errord:
		asm{
			mov ah, 09h // Instruccion para desplegar un mensaje en pantalla
			mov dx, OFFSET err // Texto a imprimir
			int 21h // Interrupcion
		}
		salir:

}

// Metodo para eliminar un directorio 
void eliminarsub(void){
	asm{
		mov ah,3Ah // Instruccion para borrar le directorio 
		mov dx,OFFSET nombreruta // Direccion a imprimir
		int 21h // instruccion de interrupcion
		jc errord
	}
	printf("subdir borrado");  // Mensaje de eliminacion de diretorio
		asm jmp salir // Salto Condicional
		errord:
		asm{
			mov ah, 09h // Instruccion para desplegar un mensaje 
			mov dx, OFFSET err // Mensaje 
			int 21h
		}
		salir:
}

// Metodo para la ruta del directorio 
void directorioa(void){
	nombrerutad[10]='$';
	asm{
		mov ah,47h // Instruccion para obtener el directorio 
		mov dl,0
		mov si,OFFSET nombrerutad // Direccion a imprimir
		int 21h
		jc mostrar_error // salto 
		mov ah, 09h // Instruccion para desplegar mensaje
		mov dx, OFFSET nombrerutad // Direccion a imprimir
		int 21h
		jmp salir	} // Salto
	mostrar_error:
	asm{
	mov dx, OFFSET err // Direccion a imprimir
	mov ah, 09h // Instruccion para desplegar mensaje
	int 21h	}
	salir:}

// Metodo para crear un archivo 
void crearAr(void){

	asm{
		mov ah, 3ch // Instruccion para crear un fichero
		mov cx, 0  
		mov dx, offset nombrearchivo // Texto a imprimir
		int 21h
		jc mostrar_error
	}
	printf("Archivo creado\n");  // Mensaje de creacion de un archivo
		asm
            jmp salir // salto
	        mostrar_error:
	asm{
	lea dx, err // lee el mensaje
	mov ah, 09h // Instruccion para desplegar un mensaje 
	int 21h
	}
	salir:
}

// Metodo para eliminar archivo
void eliminarAr(void){
	asm{
		mov ah, 41h // Instruccion para borrar el archivo 
		mov dx, offset nombrearchivo // Texto a imprimir
		int 21h // Interrupcion 21h
		jc mostrar_error
	}
	printf("Archivo borrado"); // Mensaje ed eliminacion de archivo
	asm	jmp salir //Salto 

	mostrar_error:
	asm{
	lea dx, err // lee el error
	mov ah, 09h // Instruccion para desplegar el mensaje 
	int 21h
	}
	salir:
}
 // Main donde se manda a llamar todos los metodos que se crearon anteriromente 
int main(void){
	clrscr();
	int op;

	while(op!=7)
    {

		printf("           MENU:  \n");
		printf("1) Crear subdirectorio \n");
		printf("2) Borrar subdirectorio \n");
		printf("3) Ruta actual \n");
		printf("4) Crear archivo \n");
		printf("5) Eliminar archivo \n");
		printf("6) Volumen del disco \n");
		printf("7) Salir \n");
	scanf("%d", &op);
	switch(op)
	{
			case 1: crearsub();
			printf("\n");break;
			case 2: eliminarsub();
			printf("\n"); break;
			 case 3:directorioa();
			 printf("\n");
			 break;
			case 4: crearAr();
			printf("\n");
			break;
			case 5: eliminarAr();
			printf("\n");
			break;
			case 6: printf("Volumen del disco %i\n", Volumen()); break;
			case 7: printf("al fin");
	}
    }
	getch();
	return 0;
	}
