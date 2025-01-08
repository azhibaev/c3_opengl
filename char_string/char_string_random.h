#ifndef CHAR_STRING_RANDOM_H
#define CHAR_STRING_RANDOM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <crypt.h>

#include "common_def.h"
#include "char_string.h"

#define CHAR_STRING_RANDOM_STRING_DEFAULT_SIZE 100

#define MODULE_NAME char_string_random

#include "module.h"

FUNCTION_INLINE char_string* FUNC(get)(char_string *p,
		size_t min_size,
		size_t max_size,
		unsigned int flags)
{
	size_t i = 0;
	size_t size = 0;
	char *buf = NULL;

	if ((flags & CHAR_STRING_FLAG_ADD) == 0)
	{
		char_string_reset(p);
	}
	if (min_size > 0)
	{
		size = min_size + (max_size > min_size ? (random() % (max_size - min_size)) : 0);
		p = char_string_realloc(p, size, flags);

		if (p &&
				p->buf)
		{
			buf = p->buf + p->write_pos;
			for (i = 0; i < size; i++)
			{
				*buf = 'A' + random() % 26;
				buf++;
			}
			p->write_pos += size;
			p->buf[p->write_pos] = 0;
		}
	}

	return p;
}

#undef MODULE_NAME

#include "module_undef.h"

#endif	/* CHAR_STRING_RANDOM_H */

