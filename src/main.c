#include <stdio.h>

#include "util.h"

int main() 
{
	char opt = '0';

	printf("Seleccionar n° Opcion: \n1: f) \n2: g) \n3: h) \n:> ");
	scanf("%c", &opt);

	switch (opt) 
	{
		case '1':
			printf(":)))))))))\n");
		break;

		default:
		break;
	}

	return 0;
}
