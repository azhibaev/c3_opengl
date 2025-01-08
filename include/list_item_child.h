#ifndef LIST_ITEM_CHILD_H
#define LIST_ITEM_CHILD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_def.h"
#include "list_item.h"
#include "list.h"
#define MODULE_NAME list_item_child
#define MODULE_STRUCT list_item_child_struct.h
#define MODULE_INIT list_item_child_init.h
#define MODULE_INIT_VAR list_item_child_init_var.h
#include "module.h"
FUNCTION_INLINE int FUNC(add)(T *p)
{
	int is_set = 0;
	if (p)
	{
	}
	return is_set;
}
#include "module_undef.h"
#endif	/* LIST_ITEM_CHILD_H */
