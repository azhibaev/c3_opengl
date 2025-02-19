#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FUNCTION_INLINE int FUNC(init_default)(T *p
#ifdef MODULE_INIT
#ifdef MODULE_INIT_VAR
#ifndef MODULE_INIT_VAR_H
#define MODULE_INIT_VAR_H STR(T_NAME(init_var.h))
#endif	/* MODULE_INIT_VAR_H */
)
{
	int is_init = FUNC(init)(p
#define PARAMETER(t,s) , 0
#define PARAMETER_POINTER(t,s) , (t*) 0
#define VAR(t,s)
#define VAR_POINTER(t,s)
#include MODULE_INIT_VAR_H
#undef VAR_POINTER
#undef VAR
#undef PARAMETER_POINTER
#undef PARAMETER
);
#undef MODULE_INIT_VAR_H
#else	/* MODULE_INIT_VAR */
)
{
	int is_init = FUNC(init)(p);
#endif	/* MODULE_INIT_VAR */
#else	/* MODULE_INIT */
)
{ 
	int is_init = FUNC(init)(p);
#endif	/* MODULE_INIT */

	return is_init;
}

