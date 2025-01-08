typedef struct T T;
struct T
{
	#ifdef MODULE_STRUCT
	#ifndef MODULE_STRUCT_H
	#define MODULE_STRUCT_H STR(T_NAME(struct.h))
	#endif	/* MODULE_STRUCT_H */
	#define FLAG(s) unsigned int is_ ## s:1;
	#define FLAGS(flag) \
	union \
	{ \
		unsigned int flags; \
		struct \
		{ \
			flag \
		}; \
	};
	#include "module_struct_def.h"
	#undef FLAGS
	#undef FLAG
	#undef MODULE_STRUCT_H
	#endif	/* MODULE_STRUCT */
};
