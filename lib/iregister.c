//  Created by Mohammadreza Mousavi [mohmou] on 9/5/14.
//  Updated by Masoumeh Taromirad on 11/08/16.
//  Updated by Wagner Morais and Johannes van Esch on 28/08/18.
//  Updated by Wagner Morais and Hazem Ali on 26/08/21.
//  Copyright (c) 2014 by Mohammadreza Mousavi [mohmou]. All rights reserved.

#include <stdlib.h>
#include <stdio.h>
#include "iregister.h"

void resetAll(iRegister *i)
{
	// pre-condition
	if (i == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to resetBit\n");
		return;
	}
	// reseting all bits
	i->content = 0x00000000;

	// post-condition
	if (i->content != 0x00000000)
	{
		fprintf(stderr, "Error: Could not reset all the bits\n");
		return;
	}
}

void setBit(int i, iRegister *r)
{
	// pre-condition
	if (r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to setBit\n");
		return;
	}

	// pre-condition
	if (i < 0 || i > 31)
	{
		fprintf(stderr, "Error: Invalid bit index \n");
		return;
	}

	// setting the i'th bit
	r->content |= (1u << i);

	// post-condition
	if ((r->content & (1u << i)) == 0)
	{
		fprintf(stderr, "Error: Failed to set bit \n");
		return;
	}
}

int getBit(int i, iRegister *r)
{
	// pre-condition
	if (r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to shiftLeft\n");
		return 0;
	}

	if (i < 0 || i > 31)
	{
		fprintf(stderr, "Error: Invalid bit\n");
		return 0;
	}

	int bitExtract = (r->content >> i) & 0x1;

	if (bitExtract != 1 & bitExtract != 0)
	{
		fprintf(stderr, "Error: Failed to get bit\n");
		return 0;
	}
	return bitExtract;
}

void shiftLeft(int i, iRegister *r)
{

	// pre-condition
	if (r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to shiftLeft\n");
		return;
	}

	if (i < 0 || i > 31)
	{
		fprintf(stderr, "Error: Invalid bit\n");
		return;
	}
	// to check the post condition
	iRegister r_before = *r;

	r->content = r->content << i;

	int j = 0;
	// post-condition
	for (j = 0; j < 32 - i; j++)
	{
		if (getBit(j, &r_before) != getBit(j + i, r))
		{
			fprintf(stderr, "Error: Post-condition failed (bits not shifted correctly)\n");
			return;
		}
	}

	for (j = 0; j < i; j++)
	{
		if (getBit(j, r) != 0)
		{
			fprintf(stderr, "Error: Post-condition failed (least significant bits not cleared)\n");
			return;
		}
	}
}


void resetBit(int i, iRegister *r)
{
	// pre-condition
	if (r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to resetBit\n");
		return;
	}
	// pre-condition
	if (i < 0 || i > 31)
	{
		fprintf(stderr, "Error: Invalid bit\n");
		return;
	}

	r->content &= ~(1 << i);

	// post-condition
	if ((r->content & (1 << i)) != 0)
	{
		fprintf(stderr, "Error: Failed to reset Bit\n");
		return;
	}
}
