
 // Librerias a ocupar en el programa de c 
#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>


// Declaracion de variables a ocupar 
char texto[20]="Clic me$";
char clicizq[35]="Clic izquierdo dentro de boton$";
char clicder[35]="Clic derecho dentro de boton$";
char clicizqf[35]="Clic izquierdo fuera de boton$";
char clicderf[35]="Clic derecho fuera de boton$";
char sobre[20]="Sobre boton$";
char fuera[20]="Fuera boton$";
int estado=0;
char flag='t';
int coorx=0;
int coory=0;
char fila=0;
char columna=0;

// Empieza el cuerpo del codigo

// Metodo para la ventana 
void ventana(char a,char b,char a1,char b1){
	asm{  //Instrucciones de ensamblador 
		mov ax,0600h
		mov bh,73h
		mov ch,a
		mov cl,b
		mov dh,a1  // numero de fila donde se desea colocar el cursor
		mov dl,b1  // Numero de columnas
		int 10H  // Instruccion para establecer el tamaño del cursor 
	}}


// Se inicializa el cursor  con instruciones en assembler
void inicializa_mouse(){
	asm{
		mov ax,00 // Inicializa el cursor 
		int 33h
	}}

// Muestra en mouse en pantalla
void mostrar_mouse(){
	asm{
		mov ax,01h // Muestra el apuntador del raton
		int 33h // Interrupcion del manejo del cursor
	}}

// Oculta el mouse 
void ocultar_mouse(){
	asm{
		mov ax,02h // Instruccion para ocultar el ocultar el cursor
		int 33h// Interrupcion del manejo del cursor
	}}

// Imprime el texto anteriormente declarado 
void printText(char texto[]){
	int j;	
	char letra;
	j=0;
	while(texto[j]!='$'){
		letra = texto[j];
		asm{
			mov ah,02h // Funcion para colocar el cursor 
			mov dl,letra // Imprime texto
			int 21h
		}
		j++;	}}

void posicionar_cursor(char fila,char columna){ //Atributos declarados a utilizar en el metodo 
	asm{  // Instruciones de ensamblador 
		mov ah,02h // Funcion para colocar el cursor 
		mov bh,00
		mov dh,fila // Instruccion para establecer numero de fila del cursor
		mov dl,columna // Instruccion para establces el numero de columna
		int 10h // Interrupcion de la bios 
	}}

//Metodo para limpiar la pantalla 
void cls(){.
	asm{
		mov ax,0600h //Instruccion de recorrido
		mov bh,31h // Fondo
		mov cx,0000h // Instruccion para la esquina superior izquierda
		mov dx,184Fh// Instruccion para la esquina inferiro derecha
		int 10h // Interrupcion del la bios
	}}

	// Istrucion para limpiar la pantalla 
void limpiar(char a, char b,char a1, char b1){ // Atributos declarados en el metodo
	asm{
		mov ax, 0600h //Instruccion de recorrido 
		mov bh,30h // color del pixel 
		mov cl,b  
		mov ch,a 
	
		mov dl,b1 // fila
		mov dh,a1 // columna
		int 10H
	}}


// Estado del mouse con las coordenas que se presentan en la pantalla 
void estado_mouse(){
	inicializa_mouse();
	mostrar_mouse();

	while(flag!='f'){
		asm{
			mov ax,03h // Obtine la posisicon del cursor y el estado del boton
			int 33h
			mov estado,bx
			mov coorx,cx // coordenadas del cursor en pantalla
			mov coory,dx
			mov ax,coorx
			mov bl,8
			div bl
			mov columna,al
			mov ax,coory
			mov bl,8
			div bl
			mov fila,al
		}

// Posicionamiento e instrucciones dependiendo de las instrcciones del mouse 
		limpiar(0,35,0,45);
posicionar_cursor(0,79); // Posiciona el cursor 
printf("X"); // Imprime el cursor
posicionar_cursor(0,35);
printf("(%i,%i)\n",fila,columna); //Filas y columnas del cursor 
		posicionar_cursor(24,79);
		if(estado==1){
		flag='t';			
	if(fila>9&&fila<13){
	if(columna>24&&columna<36){
	limpiar(1,20,1,55);
	posicionar_cursor(1,21);
	printText(clicizq);
	posicionar_cursor(24,79);
				}else{
					limpiar(1,20,1,55);  // Limpia 
	posicionar_cursor(1,21);
	printText(clicizqf);
	posicionar_cursor(24,79);
				}
			}else{
				limpiar(1,20,1,55);
	posicionar_cursor(1,21);
	printText(clicizqf);
	posicionar_cursor(24,79);             // Se manda a llamar lo metodos 
			}                             // anteriormente ya declarados 
	if(fila==0&&columna==79){
				flag='f';
			}
		}
		if (estado==2){
			flag='t';
	if(fila>9&&fila<13){
	if(columna>24&&columna<36){
	limpiar(1,20,1,55);
	posicionar_cursor(1,21);
	printText(clicder);
	posicionar_cursor(24,79);
	}else{
	limpiar(1,20,1,55);
	posicionar_cursor(1,21);
	printText(clicderf);
	posicionar_cursor(24,79);
				}
	}else{
	limpiar(1,20,1,55);
	posicionar_cursor(1,21);
	printText(clicderf);
	posicionar_cursor(24,79);
	}
		}
		if(fila>9&&fila<13){
	if(columna>24&&columna<36){
	limpiar(2,30,2,55);
	posicionar_cursor(2,31);
	printText(sobre);
	posicionar_cursor(24,79);
			}else{
	limpiar(2,30,2,55);
	posicionar_cursor(2,31);
	printText(fuera);
	posicionar_cursor(24,79);
			}
		}else{
			limpiar(2,30,2,55);
	posicionar_cursor(2,31);
	printText(fuera);
	posicionar_cursor(24,79);
		}
		delay(75);				
	}
}

// Metodo de ejecucion main
int main(){
    cls(); // Limpia pantalla
    ventana(10,25,12,35);
    posicionar_cursor(11,26);
    printText(texto);
    estado_mouse();
	posicionar_cursor(23,0);
	system("pause");
	return 0;
}



