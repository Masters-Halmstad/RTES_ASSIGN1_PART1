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

// code for test shiftLeft
// int main()
// {
// 	iRegister reg;		// declare a register
// 	reg.content = 0x0B; // binary: 00000000 00000000 00000000 00001011

// 	printf("Original register: 0x%08X\n", reg.content);

// 	// Test shiftLeft by 1
// 	shiftLeft(1, &reg);
// 	printf("After shiftLeft(1): 0x%08X\n", reg.content);

// 	// Reset for next test
// 	reg.content = 0x0B;

// 	// Test shiftLeft by 4
// 	shiftLeft(4, &reg);
// 	printf("After shiftLeft(4): 0x%08X\n", reg.content);

// 	// Test shiftLeft by 0 (no change)
// 	reg.content = 0x0B;
// 	shiftLeft(0, &reg);
// 	printf("After shiftLeft(0): 0x%08X\n", reg.content);

// 	// Test shiftLeft by 31 (edge case)
// 	reg.content = 0x0B;
// 	shiftLeft(31, &reg);
// 	printf("After shiftLeft(31): 0x%08X\n", reg.content);

// 	return 0;
// }

// code to test shiftRight
// int main()
// {
// 	iRegister reg;

// 	// Test 1: shiftRight(1)
// 	reg.content = 0x0B; // binary: 00000000 00000000 00000000 00001011
// 	printf("Original register: 0x%08X\n", reg.content);
// 	shiftRight(1, &reg);
// 	printf("After shiftRight(1): 0x%08X\n", reg.content);
// 	// Expected: 0x00000005 (00000000...00000101)

// 	// Test 2: shiftRight(4)
// 	reg.content = 0x0B;
// 	shiftRight(4, &reg);
// 	printf("After shiftRight(4): 0x%08X\n", reg.content);
// 	// Expected: 0x00000000 (00000000...00000000)

// 	// Test 3: shiftRight(0)
// 	reg.content = 0x0B;
// 	shiftRight(0, &reg);
// 	printf("After shiftRight(0): 0x%08X\n", reg.content);
// 	// Expected: 0x0000000B (unchanged)
// 	// but will get error , due to int data type in stucture,
// 	// on right shift on signed integer most compiler performs airthmetic shift ,
// 	// So if MSB is 1, shifting right fills in 1s instead of 0s.

// 	// Test 4: shiftRight(31)
// 	reg.content = 0x80000000; // only MSB set
// 	shiftRight(31, &reg);
// 	printf("After shiftRight(31): 0x%08X\n", reg.content);
// 	// Expected: 0x00000001 (LSB set, all others cleared)

// 	return 0;
// }

// getNibble

int main()
{
	iRegister reg;

	// Example 1
	reg.content = 0x12345678;
	int nib1 = getNibble(1, &reg);
	int nib2 = getNibble(2, &reg);

	printf("Register: 0x%08X\n", reg.content);
	printf("Nibble 1 (LSB): 0x%X\n", nib1); // Expected: 0x8
	printf("Nibble 2: 0x%X\n", nib2);		// Expected: 0x7

	// Example 2
	reg.content = 0x000000AB;  // 10101011
	nib1 = getNibble(1, &reg); // Expected 0xB
	nib2 = getNibble(2, &reg); // Expected 0xA

	printf("\nRegister: 0x%08X\n", reg.content);
	printf("Nibble 1 (LSB): 0x%X\n", nib1);
	printf("Nibble 2: 0x%X\n", nib2);

	// Example 3: Error cases
	getNibble(3, &reg); // Invalid pos
	getNibble(1, NULL); // NULL pointer

	return 0;
}