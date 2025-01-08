#ifndef LINE3F_H
#define LINE3F_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_def.h"
#include "char_string.h"
#include "list.h"
#include "color3f.h"
#include "vertex3f.h"
#define MODULE_NAME line3f
#define MODULE_STRUCT line3f_struct.h
#define MODULE_INIT line3f_init.h
#include "module.h"
FUNCTION_INLINE int FUNC(draw)(T *p)
{
	int is_set = 0;
	vertex3f *vertex = NULL;
	list_item *item = NULL;
	size_t type = 0;
	color3f *color = NULL;
	if (p)
	{
		if (p->points)
		{
			if (list_begin(p->points))
			{
				glBegin(GL_LINE_STRIP);
				while ((item = list_get_item(p->points)))
				{
					type = *((size_t*) item->item);
					if (type == draw_item_type_vertex3f)
					{
						vertex = (vertex3f*) item->item;
						glVertex3f(vertex->x,
								vertex->y,
								vertex->z);
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
				glEnd();
			}
		}
	}
	return is_set;
}
FUNCTION_INLINE int FUNC(vertex)(T *p,
		double x,
		double y,
		double z)
{
	int is_set = 0;
	vertex3f *vertex = NULL;
	if (p)
	{
		vertex = vertex3f_create_init(1,
				x,
				y,
				z);
		if (vertex)
		{
			is_set = list_add(p->points,
					vertex);
			if (!is_set)
			{
				vertex3f_free(vertex);
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
#endif	/* LINE3F_H */
