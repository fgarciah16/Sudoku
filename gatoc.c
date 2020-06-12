#include <stdio.h>
int main(){
	
	char matriz[3][3], opc; 
	int i, 
	int j;
	int fila;
	int col; 
	int ganador = 0; 
	int turno = 1;    
	
	printf("Juego del gato!\n");
	
	
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			matriz[i][j]=' ';     
			
			printf("[%c]", matriz[i][j]);
		}
		printf("\n");
	}
	
	printf("\n\nPresione Y para jugar / N para salir: ");  
	scanf("%c", &opc);
	

	
	if(opc == 'Y' || opc == 'y'){ 
		
		
		do{
			if(turno%2==1){
				do{
                  asm{
                      MOV AH,02H
                      MOV DH,21
                      MOV DL,55
                      MOV BH,0H
                      INT 10
                  }
					printf("\nJugador 1: \n");

                    asm{
                        MOV AH,02H
                        MOV DH,21
                        MOV DL,55
                        MOV BH,0H
                        INT 10
                    }
					printf("Digite fila: ");
					scanf("%d", &fila);             
					printf("Digite columna: ");
					scanf("%d", &col);
					
					if(
						matriz[fila][col] == 'x' || matriz[fila][col] == 'o' || fila > 2 || col > 2){
						printf("\nCoordenadas no validas, pruebe otra vez.\n");
					}                               
				}while(matriz[fila][col] == 'x' || matriz[fila][col] == 'o' || fila > 2 || col > 2);
				
				matriz[fila][col]='x'; 
			   
				system("cls");
				for(i=0; i<3; i++){
					for(j=0; j<3; j++){
						printf("[%c]", matriz[i][j]);
					}
					printf("\n");
				}
				turno++; 






			} else if(turno%2==0){       
				do{
					printf("\nJugador 2: \n");
					printf("Digite la fila: ");
					scanf("%d", &fila);
					printf("Digite la columna: ");
					scanf("%d", &col);
					
					if(matriz[fila][col] == 'x' || matriz[fila][col] == 'o' || fila > 2 || col > 2){
						printf("\nCoordenadas no validas, pruebe otra vez.\n");
					}
				} while(matriz[fila][col] == 'x' || matriz[fila][col] == 'o' || fila > 2 || col > 2);
				
				matriz[fila][col]='o'; 
				
				system("cls");
				for(i=0; i<3; i++){
					for(j=0; j<3; j++){
						printf("[%c]", matriz[i][j]);
					}
					printf("\n");
				}
				turno++; 
			}



			
			if(matriz[0][0] == 'x' && matriz[0][0] == matriz[0][1] && matriz[0][0] == matriz[0][2]
			|| matriz[1][0] == 'x' && matriz[1][0] == matriz[1][1] && matriz[1][0] == matriz[1][2]
			|| matriz[2][0] == 'x' && matriz[2][0] == matriz[2][1] && matriz[2][0] == matriz[2][2]
			
			|| matriz[0][0] == 'x' && matriz[0][0] == matriz[1][0] && matriz[0][0] == matriz[2][0]
			|| matriz[0][1] == 'x' && matriz[0][1] == matriz[1][1] && matriz[0][1] == matriz[2][1]
			|| matriz[0][2] == 'x' && matriz[0][2] == matriz[1][2] && matriz[0][2] == matriz[2][2]
			
			|| matriz[0][0] == 'x' && matriz[0][0] == matriz[1][1] && matriz[0][0] == matriz[2][2]
			|| matriz[0][2] == 'x' && matriz[0][2] == matriz[1][1] && matriz[0][2] == matriz[2][0]){
				ganador=1;  
				printf("\nFelicidades! Gano el jugador 1.\n");
			}
			 
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
			}
			
		} while(ganador != 1);
	} else {
		system("cls"); 
		printf("\n Que lastima! Que tengas buen dia.\n");
	}
	
	return 0;
}