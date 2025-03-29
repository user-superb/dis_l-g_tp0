#include <stdio.h>
#include <locale.h>

#include "util.h"

#include "Grupo06f.h"
#include "Grupo06g.h"
#include "Grupo06h.h"

int main()
{
	setlocale(LC_ALL, "spanish");

	/* Variables */
	const char msg[] = "Seleccionar opcion: \n1: Punto f) \n2: Punto g) \n3: Punto h) \n\n4: UNIT_TEST_LECTURA_BINARIO\n\n5: Salir\n:> ";

	char opt;

	printf(msg);
	while ((opt = readOpt()) != '5')
	{
		switch (opt)
		{
			case '1':
				f();
			break;
			case '2':
			    g();
			break;
			case '3':
				h();
			break;
			case '4':
				unitTest_readBinary();
			break;
			default:
			break;
		}

		printf(msg);
	}

	return 0;
}
