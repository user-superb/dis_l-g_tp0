#include <stdio.h>
#include <stdlib.h>

#include "util.h"

#define STR_LEN 16
#define BITS_E 7
#define BITS_D 8

void read() 
{
	/* Variables */
	unsigned int result = 0, 
		     signo,
		     aux_decimal,
		     aux_index;

	aux_decimal = aux_index = signo = 0;

	int 	aux_entero = 0;



	/* Lectura */
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



	// Comprobación del Signo 
	//
	if (binary[0] == '+')
		signo = 0;
	else if (binary[0] == '-')
		signo = 1;
	else if (binary[0] >= '0' && binary[0] <= '9' || binary[0] == '.')
		signo = 0;
	else
	{
		printf("Se detectó un caracter erroneo. (Signo)\n");
		return;
	}

	// Analizar Gramaticalmente la Parte Entera
	//
	char str_entero[100];
	if (binary[0] != '.' && binary[0] != ',')
	{
		if (signo) 
			str_entero[aux_index++] = '-';

		while (aux_index < STR_LEN-1 && binary[aux_index] != '.' && binary[aux_index] != '\0')
		{
			if (!isDigit(binary[aux_index]))
			{
				printf("Se detectó un caracter erroneo. (Entero)\n");
				return;
			}

			str_entero[aux_index] = binary[aux_index];
			aux_index++;
		}
		str_entero[aux_index] = '\0';

		aux_entero = atoi(str_entero);
		printf("str_entero: %s\n", str_entero);
		if (aux_entero > 127 )
		{
			printf("El número superó el rango.\n");
			return;
		}
	}
	
	// Analizar Gramaticalmente la Parte Decimal
	//
	char str_decimal[100];
	unsigned int j = 0;
	if (aux_index < STR_LEN - 1 && binary[aux_index] == '.')
	{
		aux_index++;
		while (binary[aux_index] != '\0' && j <= 4) // según el profesor: solo interesan los primeros 4 digitos ya que la resolución es demasiado chica como para poder representar mayor cantidad de dígitos, por lo tanto j <= 4.
		{
			if (!isDigit(binary[aux_index]))
			{
				printf("Se detectó un caracter erroneo. (Decimal)\n");
				return;
			}

			str_decimal[j] = binary[aux_index];
			aux_index++;
			j++;
		}
	}
	/* aux_decimal = atoi(str_decimal) * 256 / 10^n; n = 1, 2, 3, 4 */
	aux_decimal = (unsigned int) ((atoi(str_decimal) * (1 << BITS_D) / uintPow(10, j)));



	/* Conversión a Q(7,8) */
	result = result | (aux_entero << BITS_D) | (signo << BITS_E + BITS_D) | aux_decimal;


	/* Mostrar Resultado en Hexadecimal*/
	printf("HEX: %#04x\n", result & 0xFFFF);
}

