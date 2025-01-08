#ifndef MUL_H
#define MUL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_def.h"
#define MODULE_NAME mul
#define MODULE_STRUCT mul_struct.h
#define MODULE_INIT mul_init.h
#define MODULE_INIT_VAR mul_init_var.h
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
