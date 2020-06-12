
#include <conio.h>
#include <stdio.h>

int main()
{
    int year;

    printf( "\n   Introduzca un year: " );
    scanf( "%d", &year );

    if ( year % 4 == 0 && year % 100 != 0 || year % 400 == 0 )
        printf( "\n   El year es bisiesto" );
    else
        printf( "\n   El year no es bisiesto" );

    getch(); 

    return 0;
}