#ifndef POINT2F_H
#define POINT2F_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"

#module point2f

#struct
double x;
double y;

#init (double x, double y)
p->x = x;
p->y = y;

#include "module.h"

FUNCTION_INLINE int FUNC(print)(T *p)
{
	int is_set = 0;

	if (p)
	{
		printf("%f %f",
				p->x,
				p->y);
		is_set = 1;
	}

	return is_set;
}

#include "module_undef.h"

#endif	/* POINT2F_H */
