#include <stdio.h>
#include <limits.h>


char readOpt()
{
	char c, opt = '?';
	while((c = getchar()) != '\n' && c != EOF)
	{
		opt = c;
	}

	return opt;
}

int isDigit(char c)
{
	if (c >= '0' && c <= '9')
		return 1;

	return 0;
}

void printBinary(unsigned int binary, unsigned int n_bits) 
{
	unsigned int mask, bit, isEven = 0;

	mask = 1 << n_bits;
	while (mask)
	{
		printf("%d", (binary & mask ? 1 : 0));
		mask = mask >> 1;
	} 
}

int getSign(char binary[])
{
	// Comprobación del Signo 
	//
	if (binary[0] == '+')
		return 0;
	else if (binary[0] == '-')
		return 1;
	else if (binary[0] >= '0' && binary[0] <= '9' || binary[0] == '.')
		return 0;
	else
	{
		return -1;
	}
}

unsigned int uintPow(unsigned int value, unsigned int n)
{
	if (!n)
		return 1;

	int initial_value = value,
			i = 1;

	for (; i < n; i++)
		value *= initial_value;

	return value;
}
