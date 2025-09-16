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

void setAll(iRegister *i)
{
	// pre-condition
	if (i == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to resetBit\n");
		return;
	}
	// reseting all bits
	i->content = 0xFFFFFFFF;

	// post-condition
	if (i->content != 0xFFFFFFFF)
	{
		fprintf(stderr, "Error: Could not reset all the bits\n");
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

int getNibble(int pos, iRegister *r)
{
	// Pre-condition
	if (r == NULL)
	{
		fprintf(stderr, "Error: NULL pointer passed to getNibble\n");
		return -1; // indicate error
	}

	if (pos < 1 || pos > 2)
	{
		fprintf(stderr, "Error: Invalid nibble position (must be 1 or 2)\n");
		return -1;
	}

	// extract nibble
	int value = (r->content >> (4 * (pos - 1))) & 0xF;

	// Post-condition 
	if (value < 0 || value > 15)
	{
		fprintf(stderr, "Error: Post-condition failed: nibble out of range\n");
		return -1;
	}

	return value;
}

void assignNibble(int pos, int value, iRegister *r)
{
    // Pre-condition checks
    if (r == NULL)
    {
        fprintf(stderr, "Error: NULL pointer passed to assignNibble\n");
        return;
    }

    if (pos < 1 || pos > 2)
    {
        fprintf(stderr, "Error: Invalid nibble position (must be 1 or 2)\n");
        return;
    }

    if (value < 0 || value > 15)
    {
        fprintf(stderr, "Error: Invalid nibble value (must be 0-15)\n");
        return;
    }

    // to check the post condition
    iRegister r_before = *r;

    // Clear the target nibble first
    r->content &= ~(0xF << (4 * (pos - 1)));

    // Assign the new value to the nibble
    r->content |= (value & 0xF) << (4 * (pos - 1));

    // Post-condition checks
    if (getNibble(pos, r) != (value & 0xF))
    {
        fprintf(stderr, "Error: Post-condition failed: nibble not set correctly\n");
        return;
    }

    // Ensure other bits remain unchanged
    int j;
    for (j = 0; j < 32; j++)
    {
        if (pos == 1 && j >= 0 && j <= 3)
            continue; // skip target nibble
        if (pos == 2 && j >= 4 && j <= 7)
            continue; // skip target nibble
        if (getBit(j, r) != getBit(j, &r_before))
        {
            fprintf(stderr, "Error: Post-condition failed: other bits modified\n");
            return;
        }
    }
}

void shiftRight(int i, iRegister *r)
{
	// pre-condition
	if (r == NULL)
	{
		fprintf(stderr, "Error: A NULL pointer was given to shiftRight\n");
		return;
	}

	if (i < 0 || i > 31)
	{
		fprintf(stderr, "Error: Invalid shift amount\n");
		return;
	}

	// to check the post condition
	iRegister r_before = *r;

	r->content = r->content >> i;

	int j;

	// post-condition: check shifted bits
	for (j = i; j < 32; j++)
	{
		if (getBit(j, &r_before) != getBit(j - i, r))
		{
			fprintf(stderr, "Error: Post-condition failed (bits not shifted correctly)\n");
			return;
		}
	}

	// post-condition: check most significant i bits are 0
	for (j = 32 - i; j < 32; j++)
	{
		if (getBit(j, r) != 0)
		{
			fprintf(stderr, "Error: Post-condition failed (most significant bits not cleared)\n");
			return;
		}
	}
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
