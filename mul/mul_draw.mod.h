#ifndef MUL_DRAW_H
#define MUL_DRAW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"

#include "mul.h"
#include "list.h"
#include "graph.h"
#include "point2f.h"

#module mul_draw

#struct
draw *draw;
init color3f *text_color;
init color3f *line_color;

#init (draw *d)
p->draw = d;
color3f_hex(p->text_color,
		0x808080);
color3f_hex(p->line_color,
		0xffffff);

#include "module.h"

FUNCTION_INLINE int FUNC(list)(T *p,
		list *list)
{
	int is_set = 0;
	mul *m = NULL;
	list_item *item = NULL;
	line3f *line = NULL;
	text2f *text = NULL;
	char buf[256];

	if (p)
	{
		if (p->draw &&
				list)
		{
			line = draw_line3f(p->draw);
			text = draw_text2f(p->draw);
			if (list_begin(list))
			{
				line3f_color(line,
						p->line_color->r,
						p->line_color->g,
						p->line_color->b);
				text2f_color(text,
						p->text_color->r,
						p->text_color->g,
						p->text_color->b);
				while ((item = list_get_item(list)))
				{
					m = (mul*) item->item;
					if (m)
					{
						line3f_vertex(line,
								m->m1,
								m->m2,
								0);
						text2f_pos(text,
								m->m1,
								m->m2);
						sprintf(buf,
								"%d,%d",
								(int) m->m1,
								(int) m->m2);
						text2f_string(text,
								buf);
					}
					list_next(list);
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(point)(T *p,
		mul *m,
		size_t scale,
		size_t n,
		size_t base)
{
	int is_set = 0;
	list *list = NULL;
	size_t div = 0;
	size_t i = 0;
	mul *item  = NULL;

	if (p)
	{
		if (m)
		{
			div = 1;
			for (i = 1; i <= n; i++)
			{
				div *= base;
			}
			list = list_create_init(1,
					NULL);
			item = mul_create_init(1,
					0,
					m->m2 % div);
			list_add(list,
					item);
			item = mul_create_init(1,
					scale,
					m->m2 % div);
			list_add(list,
					item);
			FUNC(list)(p,
					list);
			list = list_create_init(1,
					NULL);
			item = mul_create_init(1,
					m->m1 % div,
					0);
			list_add(list,
					item);
			item = mul_create_init(1,
					m->m1 % div,
					scale);
			list_add(list,
					item);
			FUNC(list)(p,
					list);
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(list_point2f)(T *p,
		list *list)
{
	int is_set = 0;
	point2f *point = NULL;
	list_item *item = NULL;
	line3f *line = NULL;
	//text2f *text = NULL;
	//char buf[256];

	if (p)
	{
		if (p->draw &&
				list)
		{
			line = draw_line3f(p->draw);
			//text = draw_text2f(p->draw);
			if (list_begin(list))
			{
				line3f_color(line,
						p->line_color->r,
						p->line_color->g,
						p->line_color->b);
/*				text2f_color(text,
						p->text_color->r,
						p->text_color->g,
						p->text_color->b);
*/				while ((item = list_get_item(list)))
				{
					point = (point2f*) item->item;
					if (point)
					{
						line3f_vertex(line,
								point->x,
								point->y,
								0);
/*						text2f_pos(text,
								point->x,
								point->y);
						sprintf(buf,
								"%.1f %.1f",
								point->x,
								point->y);
						text2f_string(text,
								buf);
*/					}
					list_next(list);
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(point2f)(T *p,
		list *points,
		size_t scale,
		size_t n,
		size_t base)
{
	int is_set = 0;
	list *list = NULL;
	size_t div = 0;
	size_t i = 0;
	point2f *item  = NULL;
	point2f *point  = NULL;
	list_item *li = NULL;
	text2f *text = NULL;
	char buf[256];

	if (p)
	{
		if (points)
		{
			div = 1;
			for (i = 1; i <= n; i++)
			{
				div *= base;
			}
			text = draw_text2f(p->draw);
			text2f_color(text,
					p->text_color->r,
					p->text_color->g,
					p->text_color->b);
			if (list_begin(points))
			{
				li = list_get_item(points);
				while (li)
				{
					point = (point2f*) li->item;
					if (point)
					{
						text2f_pos(text,
								point->x,
								point->y);
						sprintf(buf,
								"%.1f %.1f",
								point->x,
								point->y);
						text2f_string(text,
								buf);
						list = list_create_init(1,
								NULL);
						item = point2f_create_init(1,
								0,
								point->y);
						list_add(list,
								item);
						item = point2f_create_init(1,
								scale,
								point->y);
						list_add(list,
								item);
						FUNC(list_point2f)(p,
								list);
						list = list_create_init(1,
								NULL);
						item = point2f_create_init(1,
								point->x,
								0);
						list_add(list,
								item);
						item = point2f_create_init(1,
								point->x,
								scale);
						list_add(list,
								item);
						FUNC(list_point2f)(p,
								list);
					}
					li = list_get_next_item(points);
				}
			}
		}
	}

	return is_set;
}

#include "module_undef.h"

#endif	/* MUL_DRAW_H */
