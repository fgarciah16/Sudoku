#include <stdio.h>
int main(){
	
	char matriz[3][3], opc; // Se declara la matriz de tres por tres 
	int i, 
	int j;
	int fila;
	int col; 
	//int frecuencia;
	int ganador = 0; 
	int turno = 1;     // Turno UNO 
	
	printf("Juego del gato!\n");
	
	
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			matriz[i][j]=' ';     // Se crea la matriz	
			printf("[%c]", matriz[i][j]); // se imprime
		}
		printf("\n");
	}
	
	printf("\n\nPresione Y para jugar / N para salir: ");  //Opcion para salir o jugar 
	scanf("%c", &opc);
	

	
	if(opc == 'Y' || opc == 'y'){ // Seleccion para jugar
		
		//Turno para el jugador uno 
		do{
			if(turno%2==1){
				do{
                  
					printf("\nJugador 1: \n");
					printf("Digite fila: ");
					scanf("%d", &fila);             
					printf("Digite columna: ");
					scanf("%d", &col);
					// Coordenadas para que no haya repeticiones en la matriz
					if(
						matriz[fila][col] == 'x' || matriz[fila][col] == 'o' || fila > 2 || col > 2){
						printf("\nCoordenadas no validas, pruebe otra vez.\n");
					}                               
				}while(matriz[fila][col] == 'x' || matriz[fila][col] == 'o' || fila > 2 || col > 2);
				
				matriz[fila][col]='x'; // Se llena la matriz del jugador 1 con x
			    //Limpa pantalla
				system("cls");
				for(i=0; i<3; i++){
					for(j=0; j<3; j++){
						printf("[%c]", matriz[i][j]);
					}
					printf("\n");
				}
				turno++; // Contador del turno 






			} else if(turno%2==0){       //Turno del segundo jugador 
				do{
					printf("\nJugador 2: \n");
					printf("Digite la fila: ");
					scanf("%d", &fila);
					printf("Digite la columna: ");
					scanf("%d", &col);
					// Coordenadas para que no haya repeticiones en la matriz
					if(matriz[fila][col] == 'x' || matriz[fila][col] == 'o' || fila > 2 || col > 2){
						printf("\nCoordenadas no validas, pruebe otra vez.\n");
					}
				} while(matriz[fila][col] == 'x' || matriz[fila][col] == 'o' || fila > 2 || col > 2);
				
				matriz[fila][col]='o'; // Se llena la matriz del jugador 2 con circulos
				
				system("cls");
				for(i=0; i<3; i++){
					for(j=0; j<3; j++){
						printf("[%c]", matriz[i][j]);
					}
					printf("\n");
				}
				turno++; // Contador para el turno 2
			}



			//  Comprobaciones para primer jugador
			if(matriz[0][0] == 'x' && matriz[0][0] == matriz[0][1] && matriz[0][0] == matriz[0][2]
			|| matriz[1][0] == 'x' && matriz[1][0] == matriz[1][1] && matriz[1][0] == matriz[1][2]
			|| matriz[2][0] == 'x' && matriz[2][0] == matriz[2][1] && matriz[2][0] == matriz[2][2]
			
			|| matriz[0][0] == 'x' && matriz[0][0] == matriz[1][0] && matriz[0][0] == matriz[2][0]
			|| matriz[0][1] == 'x' && matriz[0][1] == matriz[1][1] && matriz[0][1] == matriz[2][1]
			|| matriz[0][2] == 'x' && matriz[0][2] == matriz[1][2] && matriz[0][2] == matriz[2][2]
			
			|| matriz[0][0] == 'x' && matriz[0][0] == matriz[1][1] && matriz[0][0] == matriz[2][2]
			|| matriz[0][2] == 'x' && matriz[0][2] == matriz[1][1] && matriz[0][2] == matriz[2][0]){
				ganador=1;  // ganador
				printf("\nFelicidades! Gano el jugador 1.\n");
				sonidito();
			}
			// Comprobaciones para segundo jugador 
			if(matriz[0][0] == 'o' && matriz[0][0] == matriz[0][1] && matriz[0][0] == matriz[0][2]
			|| matriz[1][0] == 'o' && matriz[1][0] == matriz[1][1] && matriz[1][0] == matriz[1][2]
			|| matriz[2][0] == 'o' && matriz[2][0] == matriz[2][1] && matriz[2][0] == matriz[2][2]
			
			|| matriz[0][0] == 'o' && matriz[0][0] == matriz[1][0] && matriz[0][0] == matriz[2][0]
			|| matriz[0][1] == 'o' && matriz[0][1] == matriz[1][1] && matriz[0][1] == matriz[2][1]
			|| matriz[0][2] == 'o' && matriz[0][2] == matriz[1][2] && matriz[0][2] == matriz[2][2]
			
			|| matriz[0][0] == 'o' && matriz[0][0] == matriz[1][1] && matriz[0][0] == matriz[2][2]
			|| matriz[0][2] == 'o' && matriz[0][2] == matriz[1][1] && matriz[0][2] == matriz[2][0]){
				ganador=1;
				printf("\nFelicidades! Gano el jugador 2.\n");
				sonidito();
			}
			
		} while(ganador != 1);
	} else {
		system("cls"); //Limpia pantalla
		printf("\n Que lastima! Que tengas buen dia.\n");
	}
	
	return 0;

	void mute(){
		asm{
			IN AL,61H
			AND AL,0FCH
			OUT 61H, AL
		}
	}

	void tiempo(){
		asm{
			MOV AX,0
			MOV CX,0002H
			MOV DX,0424H
			MOV AH,86H
			INT 15H
		}
	}

	void beep (int frecuencia){
		asm{
			MOV BX,frecuencia
			MOV AL,BL
			OUT 42H,AL
			MOV AL,BH
			OUT 42H,AL
			IN AL,61H
			OR AL,3
			OUT 61H,AL
		}
	}

	void sonidito(){
		beep(1507);
		tiempo();
		mute();
		beep(2010);
		tiempo();
		mute();
		beep(1507);
		tiempo();
		mute();
		beep(2010);
		tiempo();
		mute();
	}
}