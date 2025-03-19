#include <stdio.h>
#include <stdlib.h>

#include "util.h"

#define STR_LEN 16

void asignarBit(unsigned int *binary, unsigned int pos)
{
	unsigned int mask = 1;

	mask = mask << pos;

	*binary = *binary | mask;
}

void read() 
{
	/*
	 *
	 * CONSTANTES
	 *
	*/
	// Q(BITS_E, BITS_D)
	const unsigned int BITS_E = 7,
	      		BITS_D = 8;

	// Lectura
	//
	printf("Ingrese un valor (+-eee.ffff): \n");
	printf("Rango decimal: %s\n", "-128.99609375 <= x <= 127.99609375");

	printf(":> ");

	int index = 0;
	char binary[STR_LEN], c;

	while ((c = getchar()) != '\n' && c != EOF && index < STR_LEN)
	{
		binary[index++] = c;
	}



	// Variables
	//
	unsigned int result = 0;
	int signo, aux_integer = 0;

	// Signo
	//
	if (binary[0] == '+')
		signo = 0;
	else if (binary[0] == '-')
		signo = 1;
	else if (binary[0] >= '0' && binary[0] <= '9')
		signo = 0;
	else
	{
		printf("Se detectó un caracter erroneo.\n");
		return;
	}

	// Parte Entera
	//
	int aux_index = 0;

	char str_entero[100];

	while (binary[aux_index] != '.' && aux_index <= 7)
	{
		str_entero[aux_index] = binary[aux_index];
		aux_index++;
	}

	aux_integer = atoi(str_entero);
	printf("Parte Entera: %d\n", aux_integer);

	if (aux_integer > 128)
	{
		printf("El número superó el rango.\n");
		return;
	}
	
	// Asignar los valores de los bits
	//
	result = result | (aux_integer << BITS_D) | (signo << BITS_E + BITS_D);
	printBinary(result, 15);
	
	int i;
	printf("\nS");
	for (i = 0; i < BITS_E; i++)
		printf("E");
	for (i = 0; i < BITS_D; i++)
		printf("D");
	printf("\n");

}

