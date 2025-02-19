#ifndef UTOPIA_MUL_H
#define UTOPIA_MUL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// module
utopia_mul

// struct
long long m1;
long long m2;
long long p;

int m(T *p)
{
	int is_set = 0;

	if (p)
	{
		p->p = p->m1 * p->m2;
		is_set = 1;
	}

	return is_set;
}

int print(T *p)
{
	int is_set = 0;

	if (p)
	{
		printf("%lld * %lld = %lld\n",
				p->m1,
				p->m2,
				p->p);
		is_set = 1;
	}

	return is_set;
}


#endif	/* UTOPIA_MUL_H */
