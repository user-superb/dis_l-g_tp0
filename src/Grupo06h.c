#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
	unsigned int i = 0;
	if (binary[0] != '.' && binary[0] != ',')
	{
		if (signo)
		{
			aux_index++;
		}
			

		while (i < STR_LEN-1 && binary[aux_index] != '.' && binary[aux_index] != '\0')
		{
			if (!isDigit(binary[aux_index]))
			{
				printf("Se detectó un caracter erroneo. (Entero)\n");
				return 0;
			}

			str_entero[i] = binary[aux_index];
			i++;
			aux_index++;
		}
		str_entero[i] = '\0';

		/* Asignación */
		aux_entero = atoi(str_entero);
		if (aux_entero > (1 << BITS_E) - 1)
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
	str_decimal[j] = '\0';

	/* Chequeos */
	if (signo)
	{
		if (str_decimal[0] != '\0') // Es equivalente a preguntar si 'str_decimal' no está vacío.
		{
			/* Asignaciones */
			aux_decimal = (unsigned int) ( (atoi(str_decimal) * (1 << BITS_F)) / uintPow(10, j));
			aux_decimal = (1 << BITS_F) - aux_decimal; // Es equivalente a calcular la diferencia entre un número decimal y 1. Por ejemplo: 1 - 0.30 = 0.70;

			aux_entero = ~aux_entero;
		} else
		{
			/* Asignaciones */
			aux_decimal = (unsigned int) ((atoi(str_decimal) * (1 << BITS_F) / uintPow(10, j)));
			aux_entero = ~(aux_entero - 1);
		}
	} else
	{
		aux_decimal = (unsigned int) ((atoi(str_decimal) * (1 << BITS_F) / uintPow(10, j)));
	}

	result = result | (aux_entero << BITS_F) | (signo << BITS_E + BITS_F) | aux_decimal;
	return result;
}


int validarX(int32_t x, int cota_sup, int cota_inf)
{
	/* Q(16,15) 32 Bits */

	int32_t mask = ~0;
	int16_t p_en, p_frac;
	p_en = p_frac = 0;

	p_en = x >> 15;
	p_frac = x & ~(mask << 15);
	printf("p_en: %d\np_frac: %x\n", p_en, p_frac);

	if (x >> 31) // Equivale a preguntar si x es negativa
	{
		// Es negativa


	}
	else
	{
		// No es negativa
	}
	return 1;
}


void h() {
    int32_t x, m, b;
    int64_t y;

    printf("VARIABLE X: ");
    x = readNumber(16,15); // Q(16,15) 32 bits
    printf("X = %08x\n", x);
	validarX(x, 100, -100);

    printf("VARIABLE m: ");
    m = readNumber(0,15);  // Q(0,15) 16 bits
    printf("m = %04x\n", m);

    printf("VARIABLE b: ");
    b = readNumber(7,8);   // Q(7,8) 16 bits
    printf("b = %04x\n", b);

    x = x >> 7;

    int64_t temp = (int64_t)x * m;  // Q(9,8) * Q(0,15) = Q(9,23)

    x = (temp + (1 << 7)) >> 8;

    // b debe permanecer con signo al desplazarse
    int64_t b_scaled = (int64_t)b << 7;

    y = x + b_scaled; // suma con signo en la misma representación

    printf("Resultado: [%08x]\n", y);
}
