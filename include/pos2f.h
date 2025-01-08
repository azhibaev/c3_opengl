#ifndef POS2F_H
#define POS2F_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_def.h"
#define MODULE_NAME pos2f
#define MODULE_STRUCT pos2f_struct.h
#define MODULE_INIT pos2f_init.h
#define MODULE_INIT_VAR pos2f_init_var.h
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
