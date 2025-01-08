#ifndef POINT2F_H
#define POINT2F_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_def.h"
#define MODULE_NAME point2f
#define MODULE_STRUCT point2f_struct.h
#define MODULE_INIT point2f_init.h
#define MODULE_INIT_VAR point2f_init_var.h
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
