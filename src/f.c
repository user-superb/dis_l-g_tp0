#include <stdio.h>
#include <stdlib.h>

#include "util.h"

#define STR_LEN 16
#define BITS_E 7
#define BITS_D 8

void read() 
{
	// Lectura
	//
	printf("Ingrese un valor (+-eee.ffff): \n");
	printf("Rango decimal: %s\n", "-128 <= x <= 127.99609375");

	printf(":> ");

	int index = 0;
	char binary[STR_LEN], c;

	while ((c = getchar()) != '\n' && c != EOF && index < STR_LEN-1)
	{
		binary[index++] = c;
	}
	binary[index] = '\0';



	// Variables
	//
	unsigned int result = 0;
	int signo, aux_entero = 0, aux_decimal = 0;

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

	while (binary[aux_index] != '.' && binary[aux_index] != '\n' && aux_index < 99)
	{
		str_entero[aux_index] = binary[aux_index];
		aux_index++;
	}
	str_entero[aux_index] = '\0';

	aux_entero = atoi(str_entero);

	if (aux_entero > 127 | (signo != 0 && aux_entero * signo < -128))
	{
		printf("El número superó el rango.\n");
		return;
	}

	// Parte Decimal
	//
	char str_decimal[100];
	unsigned int j = 0;
	if (binary[aux_index] == '.' && aux_index < 15)
	{
		//aux_index++;
		while (binary[aux_index] != '\n' && j < 99)
		{
			str_decimal[j] = binary[aux_index];
			aux_index++;
			j++;
		}
	}

	str_decimal[j] = '\0';

	aux_decimal = atoi(str_decimal);	

	printf("str_entero: %s\nstr_decimal: %s\n", str_entero, str_decimal);

	// Asignar los valores de los bits
	//
	result = result | (aux_entero << BITS_D) | (signo << BITS_E + BITS_D) ;
	result += (int) (atof(str_decimal) * 256);

	printBinary(result, 15);

	printf("\n?: %f", atof("123,1"));
	
	int i;
	printf("\nS");
	for (i = 0; i < BITS_E; i++)
		printf("E");
	for (i = 0; i < BITS_D; i++)
		printf("D");
	printf("\n");
}

