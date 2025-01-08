#ifndef LIST_ITEM_H
#define LIST_ITEM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_def.h"
#define MODULE_NAME list_item
#define MODULE_STRUCT list_item_struct.h
#define MODULE_INIT list_item_init.h
#define MODULE_INIT_VAR list_item_init_var.h
#define MODULE_FUNC_DEF list_item_func_def.h
#include "module.h"
FUNCTION_INLINE int FUNC(add_child)(T *p,
		list *child)
{
	int is_set = 0;
	if (p)
	{
		p->child = child;
		is_set = 1;
	}
	return is_set;
}
FUNCTION_INLINE list* FUNC(get_child)(T *p)
{
	list *list = NULL;
	if (p)
	{
		list = p->child;
	}
	return list;
}
#include "module_undef.h"
#endif	/* LIST_ITEM_H */
