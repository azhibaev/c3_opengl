#ifndef FIND_LINE_H
#define FIND_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"

#include "line.h"
#include "point2f.h"

#module find_line

#struct
init list *lines;
init list *lines2;
init list *points;
size_t n;
size_t n_min;
size_t n_max;

#init (size_t n_min, size_t n_max)
p->n = 0;
p->n_min = n_min;
p->n_max = n_max;

#include "module.h"

FUNCTION_INLINE int FUNC(item)(T *p,
		list_item *item);

FUNCTION_INLINE int FUNC(print_item)(T *p,
		list_item *item);
FUNCTION_INLINE int FUNC(print)(T *p);

FUNCTION_INLINE int FUNC(list)(T *p,
		list *list)
{
	int is_set = 0;
	list_item *item = NULL;

	if (p)
	{
		if (p->n < p->n_max)
		{
			p->n++;
			if (list)
			{
				if (p->n >= p->n_min &&
						p->n <= p->n_max)
				{
					list_add(p->lines,
							list);
				}
				if (list_begin(list))
				{
					item = list_get_item(list);
					while (item)
					{
						FUNC(item)(p,
								item);
						item = list_get_next_item(list);
					}
				}
				is_set = 1;
			}
			if (p->n > 0)
			{
				p->n--;
			}
			else
			{
				p->n = 0;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(item)(T *p,
		list_item *item)
{
	int is_set = 0;
	list *list = NULL;

	if (p)
	{
		if (item)
		{
			FUNC(print_item)(p,
					item);
			printf("\n");
			list = list_item_get_child(item);
			if (list)
			{
				FUNC(list)(p,
						list);
			}
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(lines)(T *p)
{
	int is_set = 0;
	list *l = NULL;
	list_item *item = NULL;
	list_item *item2 = NULL;
	mul *m = NULL;
	mul *m2 = NULL;
	line *line = NULL;

	if (p)
	{
		if (p->lines)
		{
			list_begin(p->lines);
			item = list_get_item(p->lines);
			while(item)
			{
				line = line_create_init(1,
						0,
						0);
				l = (list*) item->item;
				if (l)
				{
					list_begin(l);
					item2 = list_get_item(l);
					while (item2)
					{
						m = (mul*) item2->item;
						if (m)
						{
							if (line_test_point(line,
										m->m1,
										m->m2))
							{
								m2 = m;
								item2 = list_get_next_item(l);
								if (!item2)
								{
									list_add(p->lines2,
											line);
								}
							}
							else
							{
								list_add(p->lines2,
										line);
								line = line_create_init(1,
										0,
										0);
								if (m2)
								{
									if (line_test_point(line,
												m2->m1,
												m2->m2))
									{
									}
								}
							}
						}
					}
				}
				item = list_get_next_item(p->lines);
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(points)(T *p)
{
	int is_set = 0;
	line *l = NULL;
	line *l2 = NULL;
	list_item *item = NULL;
	list_item *item2 = NULL;
	point2f *point = NULL;

	if (p)
	{
		if (p->lines2)
		{
			list_begin(p->lines2);
			item = list_get_item(p->lines2);
			while(item)
			{
				l = (line*) item->item;
				if (l)
				{
					item2 = list_get_next_item(p->lines2);
					while(item2)
					{
						l2 = (line*) item2->item;
						if (l2)
						{
							if (l->x2 != l2->x1 &&
									l->y2 != l2->y1)
							{
								if (line_intersection(l,
											l2))
								{
									if (l->x >= l->x1 &&
											l->x <= l->x2)
									{
										if (l->x >= l2->x1 &&
													l->x <= l2->x2)
										{
											point = point2f_create_init(1,
													l->x,
													l->y);
											if (list_add(p->points,
														point))
											{
												point2f_print(point);
												printf("\n");
											}
											else
											{
												point2f_free(point);
												point = NULL;
											}
										}
									}
								}
							}
						}
						item2 = list_get_next_item(p->lines2);
					}
				}
				list_set_item(p->lines2,
						item);
				item = list_get_next_item(p->lines2);
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(print_item)(T *p,
		list_item *item)
{
	int is_set = 0;
	mul *m = NULL;

	if (p)
	{
		if (item)
		{
			m = (mul*) item->item;
			if (m)
			{
				is_set = mul_print(m);
				printf("\n");
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(print)(T *p)
{
	int is_set = 0;
	list *l = NULL;
	list_item *item = NULL;
	list_item *item2 = NULL;

	if (p)
	{
		if (p->lines)
		{
			list_begin(p->lines);
			item = list_get_item(p->lines);
			while(item)
			{
				l = (list*) item->item;
				if (l)
				{
					list_begin(l);
					item2 = list_get_item(l);
					while (item2)
					{
						FUNC(print_item)(p,
								item2);
						item2 = list_get_next_item(l);
					}
				}
				item = list_get_next_item(p->lines);
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(print_lines)(T *p)
{
	int is_set = 0;
	line *l = NULL;
	list_item *item = NULL;

	if (p)
	{
		if (p->lines2)
		{
			list_begin(p->lines2);
			item = list_get_item(p->lines2);
			while(item)
			{
				l = (line*) item->item;
				if (l)
				{
					line_print(l);
					printf("\n");
				}
				item = list_get_next_item(p->lines2);
			}
		}
	}

	return is_set;
}

#include "module_undef.h"

#endif	/* FIND_LINE_H */
