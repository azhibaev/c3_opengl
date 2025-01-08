#ifndef DRAW_H
#define DRAW_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_def.h"
#include "char_string.h"
enum draw_item_type
{
	draw_item_type_color3f,
	draw_item_type_vertex3f,
	draw_item_type_line3f,
	draw_item_type_text2f,
	draw_item_type_pos2f,
	draw_item_type_bitmap_string,
};
#include "line3f.h"
#include "text2f.h"
#define MODULE_NAME draw
#define MODULE_STRUCT draw_struct.h
#include "module.h"
FUNCTION_INLINE void* FUNC(line3f)(T *p)
{
	int is_set = 0;
	line3f *line = NULL;
	if (p)
	{
		if (p->f)
		{
			line = line3f_create_init(1);
			if (line)
			{
				is_set = list_add(p->f,
						line);
				if (!is_set)
				{
					line3f_free(line);
				}
			}
		}
	}
	return line;
}
FUNCTION_INLINE void* FUNC(text2f)(T *p)
{
	int is_set = 0;
	text2f *text = NULL;
	if (p)
	{
		if (p->f)
		{
			text = text2f_create_init(1);
			if (text)
			{
				is_set = list_add(p->f,
						text);
				if (!is_set)
				{
					text2f_free(text);
				}
			}
		}
	}
	return text;
}
FUNCTION_INLINE int FUNC(run)(T *p)
{
	int is_set = 0;
	list_item *item = NULL;
	size_t type = 0;
	if (p)
	{
		if (list_begin(p->f))
		{
			while ((item = list_get_item(p->f)))
			{
				type = *((size_t*) item->item);
				if (type == draw_item_type_line3f)
				{
					is_set += line3f_draw(item->item);
				}
				else if (type == draw_item_type_text2f)
				{
					is_set += text2f_draw(item->item);
				}
				list_next(p->f);
			}
		}
	}
	return is_set;
}
#include "module_undef.h"
#endif	/* DRAW_H */
