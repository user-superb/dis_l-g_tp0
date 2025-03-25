#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int getNumIngresado(int*);
char procesarNum(unsigned int*,unsigned int*, int);
void imprimirNumero(char,unsigned int, unsigned int);

void correrG()
{
    unsigned int parteEntera,parteFraccionaria;
    char signo;
    int numIngresado;

    if(getNumIngresado(&numIngresado))
        return;

    signo = procesarNum(&parteEntera,&parteFraccionaria,numIngresado);

    imprimirNumero(signo,parteEntera,parteFraccionaria);

    return;
}

int getNumIngresado(int* numIngresado)
{
    char entryStream[5];
    int booleano;
    do
    {
        booleano = 1;
        printf("Ingrese un numero en formato 0xHHHH: 0x");

        if(scanf("%04s",entryStream) != 1)
        {
            printf("Formato erroneo. Reingresar.\n");
            while(getchar() != '\n')
                continue;
            continue;
        }

        entryStream[4] = '\0';

        if (strlen(entryStream) > 0 && getchar() != '\n')
        {
            printf("Error: Demasiados caracteres. El formato de entrada es HHHH.\n");
            while (getchar() != '\n')
                continue;
            continue;
        }


        if (strlen(entryStream) != 4)
        {
            printf("Error: El formato de entrada es HHHH.\n");
            continue;
        }

        for (int i = 0; i < 4; i++)
        {
            if (!isxdigit(entryStream[i]))
            {
                booleano = 0;
                break;
            }
        }
        if(!booleano)
        {
            printf("\nIngrese digitos del 0 - 9 y letras del A - F.\n");
            continue;
        }
        else
            break;

    }while(1);


    booleano = sscanf(entryStream, "%X", numIngresado);

    if(booleano)
    {
        return 0;
    }
    else
    {
        printf("Error critico.");
        return 1;
    }
}

char procesarNum(unsigned int* entera,unsigned int* fracc,int numIngresado)
{
    char signo;
    int bitSignificativo = numIngresado & 0x8000;
    *entera = numIngresado & 0x7F00;
    *entera = *entera >> 8;
    if(bitSignificativo)
    {
        signo = '-';
        *entera = -((int)(0x80 - *entera));
    }

    else
        signo = '+';
    *fracc = numIngresado & 0x00FF;
    return signo;

}

void imprimirNumero(char signo,unsigned int entero, unsigned int fracc)
{
    fracc *= 10000;
    fracc /= 256;
    //Iba a chequear rangos aca, pero con formato 0xHHHH es imposible ingresar algo fuera de rango.

    if(signo == '+')
        printf("\nSu numero es %c%d.%04d",signo,entero,fracc);
    else
    {
        printf("\nSu numero es %d.%04d\n",entero,fracc);
    }
}