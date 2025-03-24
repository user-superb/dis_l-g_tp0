#include <stdio.h>
#include <stdlib.h>

#include "util.h"

unsigned int readNumber(unsigned int BITS_E, unsigned int BITS_F)
{
	/* Variables */
	const unsigned int STR_LEN = 100;

	unsigned int result = 0, 
		     signo,
		     aux_decimal,
		     aux_index;

	aux_decimal = aux_index = signo = 0;

	int 	aux_entero = 0;



	/* Lectura */
	printf("Ingrese un valor (+-eee.ffff): \n");
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
		return 0;
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
				return 0;
			}

			str_entero[aux_index] = binary[aux_index];
			aux_index++;
		}
		str_entero[aux_index] = '\0';

		aux_entero = atoi(str_entero);
		printf("str_entero: %s\n", str_entero);
		if (aux_entero > (1 << BITS_E) )
		{
			printf("El número superó el rango.\n");
			return 0;
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
				return 0;
			}

			str_decimal[j] = binary[aux_index];
			aux_index++;
			j++;
		}
	}

	aux_decimal = (unsigned int) ((atoi(str_decimal) * (1 << BITS_F) / uintPow(10, j)));



	/* Conversión a Q(7,8) */
	result = result | (aux_entero << BITS_F) | (signo << BITS_E + BITS_F) | aux_decimal;

	return result;
}

void h()
{
	unsigned int x, m, b, y;
    printf("VARIABLE X: ");
    x = readNumber(16,15); //Q(16,15) 32 bits
    printf("VARIABLE m: ");
    m = readNumber(0,15);   //Q(0,15) 16 bits
    printf("VARIABLE b: ");
    b = readNumber(7,8);    //Q(7,8) 16 bits

    x = x >> 7;  //Desplazamos x para multiplicar con m.

    unsigned int temp = x * m;  // Q(9,8) * Q(0,15) = Q(9,23)

    x = temp >> 8;  // pasa de Q(9,23) a Q(16,15)

    b = b << 7;  // Pasa de Q(7,8) a Q(16,15)

    // Sumamos en la misma representación
    y = x + b;


    printf("Resultado: [%08x]\n", y);
}
