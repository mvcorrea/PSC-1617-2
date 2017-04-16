/***
 *
 * ISEL, LEIC, Computer Systems Programming (PSC)
 *
 * IEEE 754 - double precision floating point numbers
 *
 * Display double bit-fields
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

/* constants used to represent IEEE 754 double-precision floating-point numbers */
#define DBL_FRAC_BIT		52		/* frac field bits */
#define DBL_EXP_BIT			11		/* exp field bits */
#define DBL_SIGN_BIT		1		/* sign field bits */
#define DBL_EXP_BIAS		((1 << (DBL_EXP_BIT - 1)) - 1)		/* exponent BIAS */
#define DBL_EXP_ALL_ONES	(~(~0UL << DBL_EXP_BIT))			/* all 1's exponent */
#define DBL_FRAC_ALL_ONES	(~(~0UL << DBL_FRAC_BIT))			/* all 1's frac */

/* double structure with its three bit fiels */
struct dbl_bits {
	unsigned long frac : DBL_FRAC_BIT;
	unsigned long exponent : DBL_EXP_BIT;
	unsigned long sign : DBL_SIGN_BIT;
};

/* double with three different views: a double itself; as an unsigned long, and; as three bit fields */
union dbl_union {
	double _double;
	unsigned long _ulong;
	struct dbl_bits _bits;
};

/* print_double_fields: print the values of the three fields of a double */

void print_double_fields(const char *prefix, double dvalue)
{
	union dbl_union du;
	unsigned long M;	/* the mantissa */
	int E;				/* the exponent */

	du._double = dvalue;
	printf("%-15s:%15e    ", prefix, dvalue);
	if (du._bits.exponent != 0 && du._bits.exponent != DBL_EXP_ALL_ONES) {
		/* Case 1: Normalized */
		M = du._bits.frac | (1UL << DBL_FRAC_BIT);		/* M = 1 + frac */
		E = du._bits.exponent - DBL_EXP_BIAS;			/* E = exponent - BIAS */
		printf("{ s: %d, E: %6d, M: 0x%016lx }\n", du._bits.sign, E, M);
	} else if (du._bits.exponent == 0) {
		/* Case 2 : Denormalized */
		M = du._bits.frac;			/* M = frac */
		if ( M != 0) {	/* a non-zero value */
			E = 1 - DBL_EXP_BIAS;	/* E = 1 - BIAS */
			printf("{ s: %d, E: %6d, M: 0x%016lx }\n", du._bits.sign, E, M);
		} else	/* zero */
			printf("{ %c0.0 }\n", du._bits.sign ? '-' : '+');				
	} else {
		/* Case 3: Special values */
		if (du._bits.frac == 0)
			printf("{ %cINFINITY }\n", du._bits.sign ? '-' : '+');
		else
			printf("{ NaN }\n");		
	}
}

/* print fields of some notable double numbers */
int main()
{
	union dbl_union du;

	/* print double values using constants defined in <float.h> */
	print_double_fields("DBL_MAX", DBL_MAX);
	print_double_fields("DBL_MIN", DBL_MIN);

	/* print using synthetized double values */
	/* DBL_MAX */
	du._bits.frac = DBL_FRAC_ALL_ONES;
	du._bits.exponent = DBL_EXP_ALL_ONES - 1;
	du._bits.sign = 0;
	print_double_fields("S_DBL_MAX", du._double);
	/* DBL_MIN */
	du._bits.frac = 1;
	du._bits.exponent = 1;
	du._bits.sign = 0;
	print_double_fields("S_DBL_MIN", du._double);
	
	print_double_fields("+0.0", +0.0);
	print_double_fields("-0.0", -0.0);
	print_double_fields("+0.0000001", +0.0000001);
	print_double_fields("-0.0000001", -0.0000001);
	
	print_double_fields("2.0", 2.0);
	print_double_fields("2.5", 2.5);
	print_double_fields("1.0 / 0.0", 1.0 / 0.0);		/* +infinity */
	print_double_fields("1.0 / -0.0", 1.0 / -0.0);	/* -infinity */
	print_double_fields("sqrt(-1)", sqrt(-1));		/* NaN */
	
	return 0;
}