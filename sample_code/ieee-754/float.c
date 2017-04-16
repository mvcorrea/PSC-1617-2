/***
 *
 * ISEL, LEIC, Computer Systems Programming (PSC)
 *
 * IEEE 754 - single precision floating point numbers
 *
 * Display float bit-fields
 *
 * Generate executable with: gcc -o float float.c -lm
 *
 * Carlos Martins, April 2017
 *
 ***/

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

/*
 * Floating-point value V = (-1) ^ s * M * 2 ^E
 */

/* constants used to represent IEEE 754 single-precision floating-point numbers */
#define FLT_FRAC_BIT		23		/* frac field bits */
#define FLT_EXP_BIT			8		/* exp field bits */
#define FLT_SIGN_BIT		1		/* sign field bits */
#define FLT_EXP_BIAS		((1 << (FLT_EXP_BIT - 1)) - 1)	/* exponent BIAS */
#define FLT_EXP_ALL_ONES	(~(~0U << FLT_EXP_BIT))			/* all 1's exponent */
#define FLT_FRAC_ALL_ONES	(~(~0U << FLT_FRAC_BIT))		/* all 1's frac */

/* float structure with its three bit fiels */
struct flt_bits {
	unsigned int frac : FLT_FRAC_BIT;
	unsigned int exponent : FLT_EXP_BIT;
	unsigned int sign : FLT_SIGN_BIT;
};

/* float with three different views: the float itself; as an unsigned int, and; as three bit fields */
union flt_union {
	float _float;
	unsigned int _uint;
	struct flt_bits _bits;
};

/* print_float_fields: print the values of the three fields of a float */
void print_float_fields(const char *prefix, float fvalue)
{
	union flt_union fu;
	unsigned int M;		/* the mantissa */
	int E;				/* the exponent */

	fu._float = fvalue;
	printf("%-15s:%15e    ", prefix, fvalue);
	if (fu._bits.exponent != 0 && fu._bits.exponent != FLT_EXP_ALL_ONES) {
		/* Case 1: Normalized */
		M = fu._bits.frac | (1UL << FLT_FRAC_BIT);		/* M = 1 + frac */
		E = fu._bits.exponent - FLT_EXP_BIAS;			/* E = exponent - BIAS */
		printf("{ s: %d, E: %4d, M: 0x%08x }\n", fu._bits.sign, E, M);
	} else if (fu._bits.exponent == 0) {
		/* Case 2 : Denormalized */
		M = fu._bits.frac;			/* M = frac */
		if ( M != 0) {	/* a non-zero value */
			E = 1 - FLT_EXP_BIAS;	/* E = 1 - BIAS */
			printf("{ s: %d, E: %4d, M: 0x%08x }\n", fu._bits.sign, E, M);
		} else	/* zero */
			printf("{ %c0.0 }\n", fu._bits.sign ? '-' : '+');				
	} else {
		/* Case 3: Special values */
		if (fu._bits.frac == 0)
			printf("{ %cINFINITY }\n", fu._bits.sign ? '-' : '+');
		else
			printf("{ NaN }\n");		
	}
}


/* print fields of some notable float numbers */
int main()
{
	union flt_union fu;

	/* print float values using constants defined in <float.h> */
	print_float_fields("FLT_MAX", FLT_MAX);
	print_float_fields("FLT_MIN", FLT_MIN);

	/* print using synthetized float values */
	/* FLT_MAX */
	fu._bits.frac = FLT_FRAC_ALL_ONES;
	fu._bits.exponent = FLT_EXP_ALL_ONES - 1;
	fu._bits.sign = 0;
	print_float_fields("S_FLT_MAX", fu._float);
	/* FLT_MIN */
	fu._bits.frac = 1;
	fu._bits.exponent = 0;
	fu._bits.sign = 0;
	print_float_fields("S_FLT_MIN", fu._float);
	
	/* number closer to zero */
	fu._bits.frac = 1;
	fu._bits.exponent = 0;
	fu._bits.sign = 0;
	print_float_fields("~0", fu._float);
	
	
	print_float_fields("+0.0", +0.0);
	print_float_fields("-0.0", -0.0);
	print_float_fields("+0.0000001", +0.0000001);
	print_float_fields("-0.0000001", -0.0000001);
	print_float_fields("1.5e-45", 1.5e-45);
	
	print_float_fields("2.0", 2.0);
	print_float_fields("2.5", 2.5);
	print_float_fields("1.0 / 0.0", 1.0 / 0.0);		/* +infinity */
	print_float_fields("1.0 / -0.0", 1.0 / -0.0);		/* -infinity */
	print_float_fields("sqrt(-1)", sqrt(-1));		/* NaN */
	
	return 0;
}