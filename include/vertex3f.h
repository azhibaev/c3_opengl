#ifndef VERTEX3F_H
#define VERTEX3F_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_def.h"
#define MODULE_NAME vertex3f
#define MODULE_STRUCT vertex3f_struct.h
#define MODULE_INIT vertex3f_init.h
#define MODULE_INIT_VAR vertex3f_init_var.h
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
