#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef MODULE_FUNC_DEF
#define MODULE_FUNC_DEF_H STR(T_NAME(func_def.h))
#include MODULE_FUNC_DEF_H
#undef MODULE_FUNC_DEF_H
#endif	/* MODULE_FUNC_DEF */

FUNCTION_INLINE T* FUNC(create)(size_t count
#ifdef MODULE_CREATE
#ifdef MODULE_CREATE_VAR
#ifndef MODULE_CREATE_VAR_H
#define MODULE_CREATE_VAR_H STR(T_NAME(create_var.h))
#endif	/* MODULE_CREATE_VAR_H */
#define PARAMETER(t,s) ,t s
#define VAR(t,s)
#include MODULE_CREATE_VAR_H
#undef VAR
#undef PARAMETER
)
{
#define PARAMETER(t,s)
#define VAR(t,s) t s;
#include MODULE_CREATE_VAR_H
#undef VAR
#undef PARAMETER
#undef MODULE_CREATE_VAR_H
#else	/* MODULE_CREATE_VAR */
)
{
#endif	/* MODULE_CREATE_VAR */
#else	/* MODULE_CREATE */
)
{
#endif	/* MODULE_CREATE */
	T *p = NULL;

	if (count > 0)
	{
		p = malloc(sizeof(T) * count);
		if (p)
		{
			memset(p, 0, sizeof(T) * count);
		}
	}
	if (p)
	{
		#ifdef MODULE_CREATE
		#ifndef MODULE_CREATE_H
		#define MODULE_CREATE_H STR(T_NAME(create.h))
		#endif	/* MODULE_CREATE_H */
		#include MODULE_CREATE_H
		#undef MODULE_CREATE_H
		#endif	/* MODULE_CREATE */
	}

	return p;
}

