/*
	Part of the Real-Time Embedded Systems course at Halmstad University
	Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
	All rights reserved.
	Wagner de Morais (Wagner.deMorais@hh.se)
*/

#include <stdio.h>
#include "lib/iregister.h" // include the header file for iRegister and shiftLeft
#define LINE 80

// int main()
// {
// 	iRegister r;
// 	char str[LINE];
// 	char c;
// 	int inumber, inibble, ibit, ishift = 0;
// 	// Using the uart
// 	// First, initialize and clear the channel
// 	// uart_init();
// 	// uart_clear();

// 	// To Display a string
// 	// uart_puts("String\n");

// 	// To get one character
// 	// c=uart_getc();

// 	// However, to get a number, you need to call uart_getc
// 	// multiple times until receiving a new line.
// 	// The results of each call to uart_getc can be stored into str
// 	// atoi(str) will result a number.
// }

int main()
{
	iRegister reg;		// declare a register
	reg.content = 0x0B; // binary: 00000000 00000000 00000000 00001011

	printf("Original register: 0x%08X\n", reg.content);

	// Test shiftLeft by 1
	shiftLeft(1, &reg);
	printf("After shiftLeft(1): 0x%08X\n", reg.content);

	// Reset for next test
	reg.content = 0x0B;

	// Test shiftLeft by 4
	shiftLeft(4, &reg);
	printf("After shiftLeft(4): 0x%08X\n", reg.content);

	// Test shiftLeft by 0 (no change)
	reg.content = 0x0B;
	shiftLeft(0, &reg);
	printf("After shiftLeft(0): 0x%08X\n", reg.content);

	// Test shiftLeft by 31 (edge case)
	reg.content = 0x0B;
	shiftLeft(31, &reg);
	printf("After shiftLeft(31): 0x%08X\n", reg.content);

	return 0;
}