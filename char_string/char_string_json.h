#ifndef CHAR_STRING_JSON_H
#define CHAR_STRING_JSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <crypt.h>

#include "common_def.h"

#define MODULE_NAME char_string_json

#include "module.h"

FUNCTION_INLINE char_string* FUNC(copy_char)(char_string *p,
		const char *s_key,
		const char *s_value,
		size_t s_key_size,
		size_t s_value_size,
		unsigned int flags,
		int is_first_item)
{
	char_string_compare s_cmp = {0};
	unsigned int is_set = 0;
	const char *s = NULL;
	size_t s_size = 0;
	int i = 0;

	if (s_key &&
			s_value)
	{
		if (s_key_size == 0)
		{
			s_key_size = strlen(s_key);
		}
		if (s_value_size == 0)
		{
			s_value_size = strlen(s_value);
		}
		if (s_key_size > 0)
		{
			for (i = 0; i < 2; i++)
			{
				if (i == 0)
				{
					s = s_key;
					s_size = s_key_size;
				}
				else
				{
					s = s_value;
					s_size = s_value_size;
				}
				s_cmp.pos1 = 0;
				s_cmp.pos2 = s_size;

				is_set = char_string_compare_check(&s_cmp, s, flags);

				if (is_set ||
						flags == 0 ||
						i > 0)
				{
					if (s_cmp.pos2 > s_cmp.pos1)
					{
						s_size = s_cmp.pos2 - s_cmp.pos1;
						p = char_string_realloc(p, s_size + 6, flags);
						if (p)
						{
							if ((flags & CHAR_STRING_FLAG_ADD) == 0 &&
									i == 0)
							{
								char_string_reset(p);
							}
							if (p->write_pos + s_size + 6 < p->buf_size)
							{
								if (i == 0 &&
										is_first_item == 0)
								{
									memcpy(p->buf + p->write_pos, ",", 1);
									p->write_pos++;
								}
								memcpy(p->buf + p->write_pos, "\"", 1);
								p->write_pos++;
								memcpy(p->buf + p->write_pos, s + s_cmp.pos1, s_size);
								p->write_pos += s_cmp.pos2 - s_cmp.pos1;
								memcpy(p->buf + p->write_pos, "\"", 1);
								p->write_pos++;
								if (i == 0)
								{
									memcpy(p->buf + p->write_pos, ":", 1);
									p->write_pos++;
								}
								p->buf[p->write_pos] = 0;
							}
						}
					}
					else if (is_set | CHAR_STRING_FLAG_LINE)
					{
						p = char_string_realloc(p, 10, 0);
					}
				}
			}
		}
	}

	return p;
}

#undef MODULE_NAME

#include "module_undef.h"

#endif	/* CHAR_STRING_JSON_H */

