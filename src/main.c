#include <stdio.h>
#include <locale.h>

#include "util.h"

#include "f.h"
#include "g.h"

int main() 
{
	setlocale(LC_ALL, "spanish");

	char opt;

	printf("Seleccionar n° Opcion: \n1: f) \n2: g) \n3: h) \n4: Salir\n:> ");
	while ((opt = readOpt()) != '4')
	{
		switch (opt)
		{
			case '1':
				read();
			break;
			case '2':
				do_something();
			break;

			default:
			break;
		}

		printf("Seleccionar n° Opcion: \n1: f) \n2: g) \n3: h) \n4: Salir\n:> ");
	}

	return 0;
}
