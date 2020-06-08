#include <stdio.h>
#define MAX 26
 
int main (void) 
{
    char nombre[MAX];                           //Nombre del jugador
    unsigned int sudoku[9][9];                 //Sudoku del jugador
    unsigned int flag;                        //Variable bandera
    unsigned int i,j,k;                       //Variables de control de ciclo
    
//Lectura del nombre del jugador
    
    scanf("%26[^\n]s", nombre);
    
//Se verifica que cumpla con no contenga ningun 0
    
    flag = 1;
    
    for(i = 0; i < 9; i++){  
        
        for(j = 0; j < 9; j++){            //Lectura del sudoku
            
            scanf("%u", &sudoku[i][j]);
            
            if(sudoku[i][j] == 0){ //Si en el sudoku un elemento es 0
                
                flag = 0;  //flag 1 se actualiza con 0;
                break; //Quiebra el ciclo
            }
        }
    }
   
    if(flag == 0){  //Si no cumple la condicion, el participante aun no termina el sudoku
        
        printf("%s: No finalizado",nombre);
    }
    else{ 
        
//Verifica que cumpla que en las filas y columnas no se repita ningun elemento
        
        flag = 1;
        
        for(i = 0; i < 9; i++){
            
            for(j = 0; j < 8; j++){
                
                for(k = j + 1; k < 9; k++){
                    
                    if(sudoku[i][j] == sudoku[i][k]){  //Si se repite un elemento en las filas
                        
                        flag = 0;   //flag se actualiza a 0
                        break;            //Quiebra el ciclo
                    }
                }
            }
        }

        flag = 1;
        
        for(i = 0; i < 9; i++){
            
            for(j = 0; j < 8; j++){
                
                for(k = j + 1; k < 9; k++){
                    
                    if(sudoku[j][i] == sudoku[k][i]){ //Si se repite un elemento en las columnas
                        
                        flag = 0;   //Flag cambia a 0
                        break;            //Quiebra el ciclo
                    }
                }
            }
        }
        
//------------------------------------------------------------------------
    //IMPRIMIR RESULTADO
       
        if(flag){ //Si flag es verdadero
            
            printf("%s: Logrado", nombre);         //El jugador logro completar el sudoku
        }
        else{ 
             
            printf("%s: No logrado", nombre);      //El jugador no logro completar el sudoku
        }
    }
    
    return 0;
}