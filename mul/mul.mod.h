#ifndef MUL_H
#define MUL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"

#module mul

#struct
long long m1;
long long m2;
long long p;

#init (long long m1, long long m2)
p->m1 = m1;
p->m2 = m2;
p->p = p->m1 * p->m2;

#include "module.h"

FUNCTION_INLINE int FUNC(m)(T *p)
{
	int is_set = 0;

	if (p)
	{
		p->p = p->m1 * p->m2;
		is_set = 1;
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(print)(T *p)
{
	int is_set = 0;

	if (p)
	{
		printf("%lld * %lld = %lld",
				p->m1,
				p->m2,
				p->p);
		is_set = 1;
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(print_hex)(T *p)
{
	int is_set = 0;

	if (p)
	{
		printf("%llx * %llx = %llx",
				p->m1,
				p->m2,
				p->p);
		is_set = 1;
	}

	return is_set;
}

#include "module_undef.h"

#endif	/* MUL_H */
