#ifndef BITMAP_STRING_H
#define BITMAP_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"

#module bitmap_string

#struct
size_t type;
char *buf;
size_t size;
void *font;

#init (char *s)
size_t size = 0;
p->type = draw_item_type_bitmap_string;
p->font = GLUT_BITMAP_TIMES_ROMAN_24;
if (s)
{
	size = strlen(s);
	if (p->buf &&
			p->size > size)
	{
		memcpy(p->buf,
				s,
				size);
		p->buf[size] = 0;
	}
	else
	{
		if (p->buf)
		{
			free(p->buf);
			p->size = 0;
		}
		p->buf = malloc((size + 2) * sizeof(char));
		if (p->buf)
		{
			p->size = size + 2;
			memcpy(p->buf,
					s,
					size);
			p->buf[size] = 0;
		}
	}
}

#free ()
if (p->buf)
{
	free(p->buf);
	p->buf = NULL;
	p->size = 0;
}

#include "module.h"

FUNCTION_INLINE int FUNC(print)(T *p)
{
	int is_set = 0;

	if (p)
	{
		if (p->buf)
		{
			printf("%s",
					p->buf);
			is_set = 1;
		}
	}

	return is_set;
}

#include "module_undef.h"

#endif	/* BITMAP_STRING_H */
