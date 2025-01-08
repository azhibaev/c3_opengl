#ifndef POS2F_H
#define POS2F_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"

#module pos2f

#struct
size_t type;
double x;
double y;

#init (double x, double y)
p->type = draw_item_type_pos2f;
p->x = x;
p->y = y;

#include "module.h"

FUNCTION_INLINE int FUNC(print)(T *p)
{
	int is_set = 0;

	if (p)
	{
		printf("%d%d",
				(int)(p->x),
				(int)(p->y));
		is_set = 1;
	}

	return is_set;
}

#include "module_undef.h"

#endif	/* POS2F_H */
