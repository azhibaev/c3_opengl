#ifndef TEXT2F_H
#define TEXT2F_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"
#include "char_string.h"
#include "list.h"
#include "color3f.h"
#include "pos2f.h"
#include "bitmap_string.h"

#module text2f

#struct
size_t type;
init list *points;

#init ()
p->type = draw_item_type_text2f;

#include "module.h"

FUNCTION_INLINE int FUNC(draw)(T *p)
{
	int is_set = 0;
	pos2f *pos = NULL;
	bitmap_string *s = NULL;
	color3f *color = NULL;
	list_item *item = NULL;
	size_t type = 0;

	if (p)
	{
		if (p->points)
		{
			if (list_begin(p->points))
			{
				while ((item = list_get_item(p->points)))
				{
					type = *((size_t*) item->item);
					if (type == draw_item_type_pos2f)
					{
						pos = (pos2f*) item->item;
						glRasterPos2f(pos->x, pos->y);
					}
					if (type == draw_item_type_bitmap_string)
					{
						s = (bitmap_string*) item->item;
						glutBitmapString(s->font,
								(const unsigned char*)s->buf);
					}
					else if (type == draw_item_type_color3f)
					{
						color = (color3f*) item->item;
						glColor3f(color->r,
								color->g,
								color->b);
					}
					list_next(p->points);
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(pos)(T *p,
		double x,
		double y)
{
	int is_set = 0;
	pos2f *pos = NULL;

	if (p)
	{
		pos = pos2f_create_init(1,
				x,
				y);
		if (pos)
		{
			is_set = list_add(p->points,
					pos);
			if (!is_set)
			{
				pos2f_free(pos);
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(string)(T *p,
		char *s_char)
{
	int is_set = 0;
	bitmap_string *s = NULL;

	if (p)
	{
		s = bitmap_string_create_init(1,
				s_char);
		if (s)
		{
			is_set = list_add(p->points,
					s);
			if (!is_set)
			{
				bitmap_string_free(s);
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(color)(T *p,
		double r,
		double g,
		double b)
{
	int is_set = 0;
	color3f *color = NULL;

	if (p)
	{
		color = color3f_create_init(1,
				r,
				g,
				b);
		if (color)
		{
			is_set = list_add(p->points,
					color);
			if (!is_set)
			{
				color3f_free(color);
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(next)(T *p)
{
	int is_set = 0;

	if (p)
	{
		if (p->points)
		{
			is_set = list_next(p->points);
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(begin)(T *p)
{
	int is_set = 0;

	if (p)
	{
		if (p->points)
		{
			is_set = list_begin(p->points);
		}
	}

	return is_set;
}

FUNCTION_INLINE void* FUNC(get_item)(T *p)
{
	void *item = NULL;

	if (p)
	{
		if (p->points)
		{
			item = list_get_item(p->points);
		}
	}

	return item;
}

#include "module_undef.h"

#endif	/* TEXT2F_H */
