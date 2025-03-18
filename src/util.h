#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>

void printBinary(unsigned int binary) 
{
	unsigned int mask, bit, isEven = 0;

	if (binary & 1)
		isEven = 1;

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

	if (!isEven)
		printf("0");
}

#endif
