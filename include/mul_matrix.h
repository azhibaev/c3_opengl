#ifndef MUL_MATRIX_H
#define MUL_MATRIX_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_def.h"
#define MODULE_NAME mul_matrix
#define MODULE_STRUCT mul_matrix_struct.h
#include "module.h"
FUNCTION_INLINE int FUNC(set_a)(T *p,
		long long a0,
		long long a1,
		long long a2,
		long long a3
)
{
	int is_set = 0;
	if (p)
	{
		p->a0 = a0;
		p->a1 = a1;
		p->a2 = a2;
		p->a3 = a3;
		is_set = 1;
	}
	return is_set;
}
FUNCTION_INLINE int FUNC(set_b)(T *p,
		long long b0,
		long long b1,
		long long b2,
		long long b3
)
{
	int is_set = 0;
	if (p)
	{
		p->b0 = b0;
		p->b1 = b1;
		p->b2 = b2;
		p->b3 = b3;
		is_set = 1;
	}
	return is_set;
}
FUNCTION_INLINE int FUNC(set_c)(T *p,
		long long c0,
		long long c1,
		long long c2,
		long long c3
)
{
	int is_set = 0;
	if (p)
	{
		p->c0 = c0;
		p->c1 = c1;
		p->c2 = c2;
		p->c3 = c3;
		is_set = 1;
	}
	return is_set;
}
FUNCTION_INLINE int FUNC(set_d)(T *p,
		long long d0,
		long long d1,
		long long d2,
		long long d3
)
{
	int is_set = 0;
	if (p)
	{
		p->d0 = d0;
		p->d1 = d1;
		p->d2 = d2;
		p->d3 = d3;
		is_set = 1;
	}
	return is_set;
}
FUNCTION_INLINE int FUNC(set)(T *p,
		long long x,
		long long y,
		long long z,
		long long w
)
{
	int is_set = 0;
	if (p)
	{
		p->x = x;
		p->y = y;
		p->z = z;
		p->w = w;
		is_set = 1;
	}
	return is_set;
}
FUNCTION_INLINE int FUNC(mul)(T *p)
{
	int is_set = 0;
	if (p)
	{
		p->x1 = p->a0 * p->x + p->a1 * p->y + p->a2 * p->z + p->a3 * p->w;
		p->y1 = p->b0 * p->x + p->b1 * p->y + p->b2 * p->z + p->b3 * p->w;
		p->z1 = p->c0 * p->x + p->c1 * p->y + p->c2 * p->z + p->c3 * p->w;
		p->w1 = p->d0 * p->x + p->d1 * p->y + p->d2 * p->z + p->d3 * p->w;
	}
	return is_set;
}
FUNCTION_INLINE int FUNC(print)(T *p)
{
	int is_set = 0;
	if (p)
	{
		printf("%lld %lld %lld %lld \t * %lld \t = %lld",
				p->a0,
				p->a1,
				p->a2,
				p->a3,
				p->x,
				p->x1);
		printf("\n");
		printf("%lld %lld %lld %lld \t * %lld \t = %lld",
				p->b0,
				p->b1,
				p->b2,
				p->b3,
				p->y,
				p->y1);
		printf("\n");
		printf("%lld %lld %lld %lld \t * %lld \t = %lld",
				p->c0,
				p->c1,
				p->c2,
				p->c3,
				p->z,
				p->z1);
		printf("\n");
		printf("%lld %lld %lld %lld \t * %lld \t = %lld",
				p->d0,
				p->d1,
				p->d2,
				p->d3,
				p->w,
				p->w1);
		is_set = 1;
	}
	return is_set;
}
#include "module_undef.h"
#endif	/* MUL_MATRIX_H */
