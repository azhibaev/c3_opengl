#ifndef LINE_H
#define LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"
#include "char_string.h"
#include "list.h"

#module line

#struct
size_t type;
double a;
double b;
double x;
double y;
long long x1;
long long y1;
long long x2;
long long y2;
int count;
init;

#init (double a, double b)
p->a = a;
p->b = b;
p->x = 0;
p->y = 0;
p->x1 = 0;
p->y1 = 0;
p->x2 = 0;
p->y2 = 0;
p->count = 0;
p->is_init = 0;

#include "module.h"

FUNCTION_INLINE int FUNC(cmp_point)(T *p,
		long long x,
		long long y)
{
	int is_set = 0;

	if (p)
	{
		if (p->is_init)
		{
			if ((p->y2 - p->y1) / (p->x2 - p->x1) ==
					(y - p->y1) / (x - p->x1))
			{
				is_set = 1;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(cmp)(T *p,
		long long x1,
		long long y1,
		long long x2,
		long long y2)
{
	int is_set = 0;
	double a;
	double b;

	if (p)
	{
		if (x1 != x2 &&
				y1 != y2)
		{
			a = (double)(y2 - y1) / (x2 - x1);
			b = y1 - a * x1;
			if (p->a == a &&
					p->b == b)
			{
				is_set = 1;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(set_point)(T *p,
		long long x,
		long long y)
{
	int is_set = 0;

	if (p)
	{
		if (!p->is_init)
		{
			if (!p->count)
			{
				p->x1 = x;
				p->y1 = y;
				p->count++;
				is_set = 1;
			}
			else if (p->count == 1)
			{
				if (p->x1 != x &&
						p->y1 != y)
				{
					p->x2 = x;
					p->y2 = y;
					p->a = (double)(p->y2 - p->y1) / (p->x2 - p->x1);
					p->b = p->y1 - p->a * p->x1;
					p->count++;
					p->is_init = 1;
					is_set = 1;
				}
			}
		}
	}

	return is_set;
}


FUNCTION_INLINE int FUNC(test_point)(T *p,
		long long x,
		long long y)
{
	int is_set = 0;

	if (p)
	{
		if (!p->is_init)
		{
			if (p->count < 2)
			{
				is_set = FUNC(set_point)(p,
						x,
						y);
			}
		}
		else
		{
			is_set = FUNC(cmp_point)(p,
					x,
					y);
			if (is_set)
			{
				if (p->x1 != x &&
						p->y1 != y)
				{
					p->x2 = x;
					p->y2 = y;
					p->a = (double)(p->y2 - p->y1) / (p->x2 - p->x1);
					p->b = p->y1 - p->a * p->x1;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(intersection)(T *p,
		T *p2)
{
	int is_set = 0;

	if (p)
	{
		if (p2)
		{
			if (p->a != p2->a &&
					p->b != p2->b)
			{
				p->x = (p2->b - p->b) / (p->a - p2->a);

				p->y = p->a * p->x + p->b;

				is_set = 1;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE double FUNC(get_x)(T *p,
		double y)
{
	double x = 0;

	if (p)
	{
		x = (y - p->b) / p->a;
	}

	return x;
}

FUNCTION_INLINE double FUNC(get_y)(T *p,
		double x)
{
	double y = 0;

	if (p)
	{
		y = x * p->a - p->b;
	}

	return y;
}

FUNCTION_INLINE int FUNC(print)(T *p)
{
	int is_set = 0;

	if (p)
	{
		printf("a = %f b = %f x = %f y = %f x1 = %lld y1 = %lld x2 = %lld y2 = %lld",
				p->a,
				p->b,
				p->x,
				p->y,
				p->x1,
				p->y1,
				p->x2,
				p->y2);
		is_set = 1;
	}

	return is_set;
}

#include "module_undef.h"

#endif	/* LINE_H */
