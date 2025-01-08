#ifndef FILL_H
#define FILL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_def.h"
#include "mul.h"
#include "list.h"
#include "mul_draw.h"
#define FILL_FLAG_PRINT (1 << 1)
#define MODULE_NAME fill
#define MODULE_STRUCT fill_struct.h
#define MODULE_INIT fill_init.h
#define MODULE_INIT_VAR fill_init_var.h
#include "module.h"
FUNCTION_INLINE int FUNC(row_dec)(T *p,
		list *list,
		list_item *parent,
		size_t n)
{
	int is_set = 0;
	size_t i = 0;
	size_t j = 0;
	mul *m = NULL;
	long long rem = 0;
	long long i_min = 0;
	long long j_min = 0;
	long long i_max = 0;
	long long j_max = 0;
	long long i_step = 0;
	long long j_step = 0;
	long long div = 0;
	size_t m_count = 0;
	list_item *item = NULL;
	size_t i_print_col = 0;
	if (p)
	{
		if (parent)
		{
			m = (mul*) parent->item;
			if (m)
			{
				i_min = m->m1;
				j_min = m->m2;
			}
		}
		div = 1;
		for (i = 1; i < n; i++)
		{
			div *= p->base;
		}
		i_step = div;
		j_step = div;
		i_max = i_min + i_step * p->base;
		j_max = j_min + j_step * p->base;
		div *= p->base;
		rem = p->ab % div;
		if (p->is_print)
		{
			printf("\nab = %lld; i_min = %lld; j_min = %lld; i_step = %lld; rem = %lld; n = %ld\n",
					p->ab,
					i_min,
					j_min,
					i_step,
					rem,
					n);
		}
		for (i = i_min; i < i_max; i += i_step)
		{
			for (j = j_min; j < j_max; j += j_step)
			{
				if ((i * j) % div == rem)
				{
					m = mul_create_init(1,
							i,
							j);
					if (p->is_print)
					{
						mul_print(m);
						if (i_print_col < 4)
						{
							printf("\t");
							i_print_col++;
						}
						else
						{
							printf("\n");
							i_print_col = 0;
						}
					}
					if (!m_count &&
							parent)
					{
						list = list_create(1);
						list_item_add_child(parent,
								list);
						item = list_item_create_init(1,
								m);
						list_add_end(list,
								item);
					}
					else
					{
						item = list_item_create_init(1,
								m);
						list_add_end(list,
								item);
					}
					m_count++;
				}
			}
		}
		is_set = m_count;
	}
	return is_set;
}
FUNCTION_INLINE int FUNC(row_hex)(T *p,
		list *list,
		list_item *parent,
		size_t n)
{
	int is_set = 0;
	size_t i = 0;
	size_t j = 0;
	mul *m = NULL;
	long long rem = 0;
	long long i_min = 0;
	long long j_min = 0;
	long long i_max = 0;
	long long j_max = 0;
	long long i_step = 0;
	long long j_step = 0;
	long long div = 0;
	size_t m_count = 0;
	list_item *item = NULL;
	size_t i_print_col = 0;
	if (p)
	{
		if (parent)
		{
			m = (mul*) parent->item;
			if (m)
			{
				i_min = m->m1;
				j_min = m->m2;
			}
		}
		div = 1;
		for (i = 1; i < n; i++)
		{
			div *= p->base;
		}
		i_step = div;
		j_step = div;
		i_max = i_min + i_step * p->base;
		j_max = j_min + j_step * p->base;
		div *= p->base;
		rem = p->ab % div;
		if (p->is_print)
		{
			printf("\nab = %llx; i_min = %llx; j_min = %llx; i_step = %llx; rem = %llx; n = %ld\n",
					p->ab,
					i_min,
					j_min,
					i_step,
					rem,
					n);
		}
		for (i = i_min; i < i_max; i += i_step)
		{
			for (j = j_min; j < j_max; j += j_step)
			{
				if ((i * j) % div == rem)
				{
					m = mul_create_init(1,
							i,
							j);
					if (p->is_print)
					{
						mul_print_hex(m);
						if (i_print_col < 4)
						{
							printf("\t");
							i_print_col++;
						}
						else
						{
							printf("\n");
							i_print_col = 0;
						}
					}
					if (!m_count &&
							parent)
					{
						list = list_create(1);
						list_item_add_child(parent,
								list);
						item = list_item_create_init(1,
								m);
						list_add_end(list,
								item);
					}
					else
					{
						item = list_item_create_init(1,
								m);
						list_add_end(list,
								item);
					}
					m_count++;
				}
			}
		}
		is_set = m_count;
	}
	return is_set;
}
FUNCTION_INLINE int FUNC(row)(T *p,
		list *list,
		list_item *parent,
		size_t n)
{
	int is_set = 0;
	if (p)
	{
		if (p->base == 10)
		{
			is_set = FUNC(row_dec)(p,
					list,
					parent,
					n);
		}
		else if (p->base == 16)
		{
			is_set = FUNC(row_hex)(p,
					list,
					parent,
					n);
		}
	}
	return is_set;
}
FUNCTION_INLINE int FUNC(row_n)(T *p,
		list *list,
		list_item *parent,
		size_t i,
		size_t n);
FUNCTION_INLINE int FUNC(n)(T *p,
		list *list,
		list_item *parent,
		size_t i,
		size_t n)
{
	int is_set = 0;
	list_item *item = NULL;
	mul *m = NULL;
	if (p)
	{
		item = parent;
		if (i <= n)
		{
			if (item)
			{
				list = list_item_get_child(item);
			}
			if (list)
			{
				list_begin(list);
				item = list_get_item(list);
			}
			while (item)
			{
				is_set += FUNC(row_n)(p,
						list,
						item,
						i,
						n);
				if (item &&
						item->child)
				{
					m = (mul*) item->item;
					if (m &&
							p->draw)
					{
						color3f_hsv(p->draw->line_color,
								((m->m1 % 10) * 10 + (m->m2 % 10)) * 360 / 100,
								1,
								1);
					}
					if (p->draw)
					{
						color3f_print(p->draw->line_color);
					}
					mul_draw_list(p->draw,
							item->child);
					printf("\n");
				}
				list_next(list);
				item = list_get_item(list);
			}
			mul_draw_list(p->draw,
					list);
		}
	}
	return is_set;
}
FUNCTION_INLINE int FUNC(row_n)(T *p,
		list *list,
		list_item *parent,
		size_t i,
		size_t n)
{
	int is_set = 0;
	list_item *item = NULL;
	if (p)
	{
		item = parent;
		if (i <= n)
		{
			is_set += FUNC(row)(p,
					list,
					item,
					i);
			is_set += FUNC(n)(p,
					list,
					item,
					i + 1,
					n);
		}
	}
	return is_set;
}
FUNCTION_INLINE int FUNC(set_flags)(T *p,
		unsigned int flags)
{
	int is_set = 0;
	if (p)
	{
		if (flags & FILL_FLAG_PRINT)
		{
			p->is_print = 1;
		}
	}
	return is_set;
}
FUNCTION_INLINE int FUNC(mul_eq)(list_item *i1,
		list_item *i2)
{
	int is_set = 0;
	mul *m1 = NULL;
	mul *m2 = NULL;
	if (i1 &&
			i2)
	{
		m1 = (mul*) i1->item;
		m2 = (mul*) i2->item;
		if (m1 &&
				m2)
		{
			if (m1->m1 == m2->m1 &&
					m1->m2 == m2->m2)
			{
				is_set = 1;
			}
			else if (m1->m1 == m2->m2 &&
					m1->m2 == m2->m1)
			{
				is_set = 1;
			}
		}
	}
	return is_set;
}
#include "module_undef.h"
#endif	/* FILL_H */
