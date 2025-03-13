#include <stdio.h>

void printBinary(unsigned int binary) 
{
	unsigned int mask, bit;

	while (binary != 0)
	{
		mask = 0x7fffffffU;
		mask = ~mask;

		bit = binary & mask;
		
		if (bit)
		{
			printf("1");	
		} else
		{
			printf("0");
		}

		binary = binary << 1;
	} 
}

int main() 
{
	printBinary(11);

	return 0;
}
