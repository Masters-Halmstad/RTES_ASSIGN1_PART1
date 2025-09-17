/*
	Part of the Real-Time Embedded Systems course at Halmstad University
	Copyright (c) 2017, Sebastian Kunze <sebastian.kunze@hh.se>
	All rights reserved.
	Wagner de Morais (Wagner.deMorais@hh.se)
*/

#include <stdio.h>
#include <stdlib.h>
#include <uart.h>
#include "lib/iregister.h" // include the header file for iRegister and shiftLeft
#define LINE 80

// void  checkShiftLeft (){
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

void stringInput(char *str)
{
	char c;
	int index = 0;
	while (1)
	{
		c = uart_getc();
		if (c == '\n' || c == '\r')
		{
			str[index] = '\0';
			break;
		}
		if (index < LINE - 1)
		{
			str[index] = c;
			index++;
		}
	};
}

int main()
{
	iRegister r;
	char name[LINE];
	char str[LINE];
	char intIntoString[LINE];
	int inumber, inibble, ibit, ishift = 0;
	char *stringBit; // to store the bits in string form

	// initializing and clearing the channel
	uart_init();
	uart_clear();

	uart_puts("========= RTES Assignement 1 Part 1 =========================");
	// input name
	uart_puts("Enter your name: ");
	stringInput(name);
	uart_puts("\n");

	// print welcome message
	uart_puts('Welcome, ');
	uart_puts(str);
	uart_puts('\n');

	// input integer number
	uart_puts("Enter a integer number (32 bit): ");
	stringInput(str);
	inumber = atoi(str);
	uart_puts(inumber);
	uart_puts('\n');

	// input bit position
	uart_puts("Enter the bit position (0<=ibit<=31): ");
	stringInput(str);
	ibit = atoi(str);
	uart_puts(ibit);
	uart_puts('\n');

	// input nibble position
	uart_puts("Enter the nibble position (0<=inibble<=2): ");
	stringInput(str);
	inibble = atoi(str);
	uart_puts(inibble);
	uart_puts('\n');

	// input number of bits to shift position
	uart_puts("Enter the number of bits to shift (0<=inibble<=2): ");
	stringInput(str);
	inibble = atoi(str);
	uart_puts(inibble);
	uart_puts('\n');

	// Print the entered message
	uart_puts("You Entered: ");
	uart_puts("Number: ");
	stringBit = reg2str(inumber);
	uart_puts(stringBit);
	free(stringBit);
	uart_puts('\n');

	uart_puts("Bit: ");
	uart_puts(ibit);
	uart_puts(",");
	uart_puts("Nibble: ");
	uart_puts(inibble);
	uart_puts('\n');

	// to reset all bits
	r.content = inumber;
	resetAll(&r);
	uart_puts("resetAll(&r) returned ");
	uart_puts(reg2str(r));
	uart_puts("\n");

	// to set all bits
	r.content = inumber;
	setAll(&r);
	uart_puts("setAll(&r) returned ");
	uart_puts(reg2str(r));
	uart_puts("\n");

	// to set bit
	r.content = inumber;
	setBit(ibit, &r);
	uart_puts("setBit(&r) returned ");
	uart_puts(reg2str(r));
	uart_puts("\n");

	// get bit
	r.content = inumber;
	getBit(inumber, &r);
	uart_puts("getBit(i, &r) returned ");
	uart_puts(reg2str(r));
	uart_puts("\n");

	// get bit
	r.content = inumber;
	getBit(ibit, &r);
	uart_puts("getBit(i, &r) returned ");
	uart_puts(reg2str(r));
	uart_puts("\n");

	// get nibble
	r.content = inumber;
	getNibble(inibble, &r);
	uart_puts("getNibble(i, &r) returned ");
	uart_puts(reg2str(r));
	uart_puts("\n");

	// get assignNibble
	r.content = inumber;
	assignNibble(inibble, inumber, &r);
	uart_puts("assignNibble(inibble, inumber, &r) returned ");
	uart_puts(reg2str(r));
	uart_puts("\n");

	// get shiftLeft
	r.content = inumber;
	shiftLeft(ibit, &r);
	uart_puts("shiftLeft(ibit, &r) returned ");
	uart_puts(reg2str(r));
	uart_puts("\n");

	// get shiftRight
	r.content = inumber;
	shiftRight(ibit, &r);
	uart_puts("shiftRight(ibit, &r) returned ");
	uart_puts(reg2str(r));
	uart_puts("\n");

	// get shiftRight
	r.content = inumber;
	resetBit(ibit, &r);
	uart_puts("resetBit(ibit, &r) returned ");
	uart_puts(reg2str(r));
	uart_puts("\n");

	// Using the uart
	// First, iniialize and clear the channel
	// uart_init();
	// uart_clear();

	// To Display a string
	// uart_puts("String\n");

	// To get one character
	// c=uart_getc();

	// However, to get a number, you need to call uart_getc
	// multiple times until receiving a new line.
	// The results of each call to uart_getc can be stored into str
	// atoi(str) will result a number.
}

// code for test shiftLeft
// int main()
// {

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

// int main()
// {
// 	iRegister reg;

// 	// Example 1
// 	reg.content = 0x12345678;
// 	int nib1 = getNibble(1, &reg);
// 	int nib2 = getNibble(2, &reg);

// 	printf("Register: 0x%08X\n", reg.content);
// 	printf("Nibble 1 (LSB): 0x%X\n", nib1); // Expected: 0x8
// 	printf("Nibble 2: 0x%X\n", nib2);		// Expected: 0x7

// 	// Example 2
// 	reg.content = 0x000000AB;  // 10101011
// 	nib1 = getNibble(1, &reg); // Expected 0xB
// 	nib2 = getNibble(2, &reg); // Expected 0xA

// 	printf("\nRegister: 0x%08X\n", reg.content);
// 	printf("Nibble 1 (LSB): 0x%X\n", nib1);
// 	printf("Nibble 2: 0x%X\n", nib2);

// 	// Example 3: Error cases
// 	getNibble(3, &reg); // Invalid pos
// 	getNibble(1, NULL); // NULL pointer

// 	return 0;
// }

// int assignNible()
// {
// 	iRegister reg;

// 	// Test 1
// 	reg.content = 0x00000000;
// 	assignNibble(1, 0xA, &reg);
// 	printf("After assignNibble(1, 0xA): 0x%08X\n", reg.content); // Expected: 0x0000000A

// 	// Test 2
// 	reg.content = 0x00000000;
// 	assignNibble(2, 0xF, &reg);
// 	printf("After assignNibble(2, 0xF): 0x%08X\n", reg.content); // Expected: 0x000000F0

// 	// Test 3
// 	reg.content = 0xFFFFFFFF;
// 	assignNibble(1, 0x0, &reg);
// 	printf("After assignNibble(1, 0x0): 0x%08X\n", reg.content); // Expected: 0xFFFFFFF0

// 	// Test 4
// 	reg.content = 0x12345678;
// 	assignNibble(2, 0x5, &reg);
// 	printf("After assignNibble(2, 0x5): 0x%08X\n", reg.content); // Expected: 0x12345578

// 	// Test 5: Invalid value
// 	assignNibble(1, 20, &reg); // Error: invalid value
// 	// Test 6: Invalid pos
// 	assignNibble(3, 0xA, &reg); // Error: invalid pos
// 	// Test 7: NULL pointer
// 	assignNibble(1, 0x5, NULL); // Error: NULL pointer

// 	return 0;
// }

int reg2str()
{
	iRegister reg;
	char *str;

	// Test 1: All bits reset
	reg.content = 0x00000000;
	str = reg2str(reg);
	printf("reg2str(0x00000000): %s\n", str); // Expected: 32 zeros
	free(str);

	// Test 2: All bits set
	reg.content = 0xFFFFFFFF;
	str = reg2str(reg);
	printf("reg2str(0xFFFFFFFF): %s\n", str); // Expected: 32 ones
	free(str);

	// Test 3: Only LSB set
	reg.content = 0x00000001;
	str = reg2str(reg);
	printf("reg2str(0x00000001): %s\n", str); // Expected: 31 zeros + "1"
	free(str);

	// Test 4: Only MSB set
	reg.content = 0x80000000;
	str = reg2str(reg);
	printf("reg2str(0x80000000): %s\n", str); // Expected: "1" + 31 zeros
	free(str);

	return 0;
}