#ifndef BITMAP_STRING_H
#define BITMAP_STRING_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_def.h"
#define MODULE_NAME bitmap_string
#define MODULE_STRUCT bitmap_string_struct.h
#define MODULE_INIT bitmap_string_init.h
#define MODULE_INIT_VAR bitmap_string_init_var.h
#define MODULE_FREE bitmap_string_free.h
#include "module.h"
FUNCTION_INLINE int FUNC(print)(T *p)
{
	int is_set = 0;
	if (p)
	{
		if (p->buf)
		{
			printf("%s",
					p->buf);
			is_set = 1;
		}
	}
	return is_set;
}
#include "module_undef.h"
#endif	/* BITMAP_STRING_H */
