#ifndef VERTEX3F_H
#define VERTEX3F_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"

#module vertex3f

#struct
size_t type;
double x;
double y;
double z;

#init (double x, double y, double z)
p->type = draw_item_type_vertex3f;
p->x = x;
p->y = y;
p->z = z;

#include "module.h"

FUNCTION_INLINE int FUNC(print)(T *p)
{
	int is_set = 0;

	if (p)
	{
		printf("%2x%2x%2x",
				(int)(p->x * 256),
				(int)(p->y * 256),
				(int)(p->z * 256));
		is_set = 1;
	}

	return is_set;
}

#include "module_undef.h"

#endif	/* VERTEX3F_H */
