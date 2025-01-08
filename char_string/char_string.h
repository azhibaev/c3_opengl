#ifndef CHAR_STRING_H
#define CHAR_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <crypt.h>

#include "common_def.h"

#define CHAR_STRING_DEFAULT_BUFFER_SIZE 1 KB
#define CHAR_STRING_RANDOM_STRING_DEFAULT_SIZE 100
#define CHAR_STRING_DEFAULT_GROWTH_FACTOR 1.5

#define CHAR_STRING_FLAG_TRIM 			(1 << 2)
#define CHAR_STRING_FLAG_ADD 			(1 << 3)
#define CHAR_STRING_FLAG_LINE 			(1 << 4)
#define CHAR_STRING_FLAG_ALPHA_UPPER 	(1 << 5)
#define CHAR_STRING_FLAG_ALPHA_LOWER 	(1 << 6)
#define CHAR_STRING_FLAG_ALPHA 	(CHAR_STRING_FLAG_ALPHA_UPPER | CHAR_STRING_FLAG_ALPHA_LOWER)
#define CHAR_STRING_FLAG_NUM 			(1 << 7)
#define CHAR_STRING_FLAG_ALNUM 	(CHAR_STRING_FLAG_ALPHA | CHAR_STRING_FLAG_NUM)
#define CHAR_STRING_FLAG_WHITESPACE		(1 << 8)
#define CHAR_STRING_FLAG_START			(1 << 9)
#define CHAR_STRING_FLAG_END			(1 << 10)
#define CHAR_STRING_FLAG_CURRENT		(1 << 11)
#define CHAR_STRING_FLAG_DOMAIN			(1 << 12)
#define CHAR_STRING_FLAG_BINARY			(1 << 13)
#define CHAR_STRING_FLAG_SKIP_READ		(1 << 14)
#define CHAR_STRING_FLAG_IDENTIFIER		(1 << 15)

#define CHAR_STRING_MAKE_STRINGIFY(s) #s
#define CHAR_STRING_UNDERSCORE "_"
#define CHAR_STRING_DASH "-"

#include "char_string_compare.h"

#define MODULE_NAME char_string

#define MODULE_STRUCT				char_string_struct.h

#define MODULE_INIT					char_string_init.h
#define MODULE_INIT_VAR				char_string_init_var.h
#define MODULE_INIT_BUF_SIZE
#define MODULE_FREE					char_string_free.h

#include "module.h"

FUNCTION_INLINE int FUNC(check)(T *p);
FUNCTION_INLINE int FUNC(check_init)(T *p);

#include "char_string_utils.h"
#include "char_string_copy.h"
//#include "char_string_read_char.h"
#include "char_string_write_char.h"
//#include "char_string_read_file.h"
#include "char_string_print.h"
#include "char_string_mark.h"
#include "char_string_step.h"

FUNCTION_INLINE int FUNC(check)(T *p)
{
	int is_set = 0;

	if (p)
	{
		if (p->is_init &&
				p->buf &&
				p->read_pos < p->write_pos &&
				p->write_pos <= p->buf_size)
		{
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(check_init)(T *p)
{
	int is_set = 0;

	if (p)
	{
		if (p->is_init &&
				p->buf &&
				p->read_pos <= p->write_pos &&
				p->write_pos <= p->buf_size)
		{
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(replace_char)(T *p,
		char from_char,
		char to_char)
{
	int is_replace = 0;
	int i = 0;

	if (p)
	{
		for (i = 0; i < p->buf_size; i++)
		{
			if (p->buf[i] == from_char)
			{
				p->buf[i] = to_char;
			}
			else if (p->buf[i] == '\0')
			{
				break;
			}
		}
		is_replace = 1;
	}

	return is_replace;
}

FUNCTION_INLINE int FUNC(char_cmp)(T *p,
		const char *s,
		size_t s_size,
		unsigned int flags)
{
	int is_cmp = 1;
	T_NAME(compare) s_cmp = {0};
	unsigned int is_set = 0;
	size_t size = 0;

	if (p && 
			s &&
			s_size > 0)
	{
		if (p->is_init &&
				p->buf)
		{
			if (p->read_pos < p->write_pos &&
					p->write_pos <= p->buf_size)
			{
				s_cmp.pos1 = p->read_pos;
				s_cmp.pos2 = p->write_pos;

				is_set = FUNC(compare_check)(&s_cmp, p->buf, flags);

				if (is_set ||
						flags == 0)
				{
					if (s_cmp.pos1 < s_cmp.pos2)
					{
						size = s_cmp.pos2 - s_cmp.pos1;
						if (size > s_size)
						{
							size = s_size;
						}
						if (size == s_size)
						{
							is_cmp = strncmp(p->buf + s_cmp.pos1, s, size);
						}
						if (is_cmp == 0)
						{
							p->cmp_pos = s_cmp.pos1;
							p->cmp_size = size;
						}
					}
				}
			}
		}
	}

	return is_cmp;
}

FUNCTION_INLINE int FUNC(cmp)(T *p,
		T *p_s,
		unsigned int flags)
{
	int is_cmp = 1;

	if (p &&
			p_s)
	{
		if (p_s->buf &&
				p_s->read_pos < p_s->write_pos &&
				p_s->write_pos <= p_s->buf_size)
		{
			is_cmp = FUNC(char_cmp)(p,
					p_s->buf + p_s->read_pos,
					p_s->write_pos - p_s->read_pos,
					flags);
		}
	}

	return is_cmp;
}

FUNCTION_INLINE int FUNC(char_cmp_line)(T *p,
		const char *s,
		unsigned int flags)
{
	int is_cmp = 1;
	size_t i_p = 0;
	size_t i_s = 0;
	size_t i_p_max = 0;
	size_t i_s_max = 0;

	if (p && s)
	{
		if (p->buf_size > p->read_pos)
		{
			i_p = p->read_pos;
			i_p_max = p->write_pos - (p->write_pos > 0 ? 1 : 0);
			if (flags & CHAR_STRING_FLAG_TRIM)
			{
				while (i_p_max > p->read_pos)
				{
					if (p->buf[i_p_max] == ' ' ||
							p->buf[i_p_max] == '\r' ||
							p->buf[i_p_max] == '\n' ||
							p->buf[i_p_max] == '\t')
					{
						if (i_p_max > 0)
						{
							i_p_max--;
						}
						else
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
				while (i_p < i_p_max)
				{
					if (p->buf[i_p] == ' ' ||
							p->buf[i_p] == '\r' ||
							p->buf[i_p] == '\n' ||
							p->buf[i_p] == '\t')
					{
						if (i_p + 1 < i_p_max)
						{
							i_p++;
						}
						else
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
			}
			i_s = 0;
			i_s_max = strlen(s);
			if (flags & CHAR_STRING_FLAG_TRIM)
			{
				while (i_s_max > i_s)
				{
					if (p->buf[i_s_max] == ' ' ||
							p->buf[i_s_max] == '\r' ||
							p->buf[i_s_max] == '\n' ||
							p->buf[i_s_max] == '\t')
					{
						if (i_s_max > 0)
						{
							i_s_max--;
						}
						else
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
				while (i_s < i_s_max)
				{
					if (p->buf[i_s] == ' ' ||
							p->buf[i_s] == '\r' ||
							p->buf[i_s] == '\n' ||
							p->buf[i_s] == '\t')
					{
						if (i_s + 1 < i_s_max)
						{
							i_s++;
						}
						else
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
			}
			while (1)
			{
				if (p->buf[i_p] != s[i_s])
				{
					break;
				}
				if (i_p < i_p_max)
				{
					i_p++;
				}
				else
				{
					is_cmp = 0;
					break;
				}
				if (i_s < i_s_max)
				{
					i_s++;
				}
				else
				{
					is_cmp = 0;
					break;
				}
			}
		}
	}

	return is_cmp;
}

FUNCTION_INLINE int FUNC(next_line)(T *p)
{
	int is_set = 0;
	size_t i = 0;

	if (p)
	{
		if (p->read_pos < p->write_pos &&
				p->write_pos <= p->buf_size)
		{
			i = p->read_pos;
			while (i < p->write_pos)
			{
				if (p->buf[i] == '\r' ||
						p->buf[i] == '\n' ||
						p->buf[i] == '\0')
				{
					i++;
					if (i <= p->write_pos)
					{
						p->read_pos = i;
						is_set = 1;
					}
					break;
				}
				i++;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(skip_new_line)(T *p,
		int is_all)
{
	int is_set = 0;
	size_t i = 0;

	if (p)
	{
		if (p->read_pos < p->write_pos &&
				p->write_pos <= p->buf_size)
		{
			i = p->read_pos;
			while (i < p->write_pos)
			{
				if (p->buf[i] == '\r' ||
						p->buf[i] == '\n' ||
						p->buf[i] == '\0')
				{
					if (is_all)
					{
						while (i <= p->write_pos)
						{
							if (p->buf[i] != '\r' &&
									p->buf[i] != '\n')
							{
								p->read_pos = i;
								is_set = 1;
								break;
							}
							i++;
						}
						break;
					}
					else
					{
						i++;
						if (i <= p->write_pos)
						{
							p->read_pos = i;
							is_set = 1;
						}
						break;
					}
				}
				i++;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE T* FUNC(add_char)(T *p,
		const char *s,
		size_t s_size,
		unsigned int flags)
{
	if (p &&
			s)
	{
		if (s_size == 0)
		{
			s_size = strlen(s);
		}
		p = FUNC(realloc)(p, s_size, CHAR_STRING_FLAG_ADD);
		if (p)
		{
			memcpy(p->buf + p->write_pos, s, s_size);
			p->write_pos += s_size;
			p->buf[p->write_pos] = 0;
		}
	}

	return p;
}

FUNCTION_INLINE T* FUNC(add)(T *p,
		T *p_s,
		unsigned int flags)
{
	if (p &&
			p_s)
	{
		if (p_s->buf &&
				p_s->read_pos < p_s->write_pos &&
				p_s->write_pos <= p_s->buf_size)
		{
			p = FUNC(add_char)(p,
					p_s->buf + p_s->read_pos,
					p_s->write_pos - p_s->read_pos,
					flags);
		}
	}

	return p;
}

FUNCTION_INLINE size_t FUNC(find_char)(T *p,
		size_t pos,
		char ch)
{
	size_t i = 0;
	size_t pos1 = 0;

	if (p)
	{
		if (p->buf)
		{
			i = pos;
			if (p->read_pos <= i &&
					p->read_pos < p->write_pos &&
					p->write_pos <= p->buf_size)
			{
				while (1)
				{
					if (i < p->write_pos)
					{
						if (p->buf[i] == ch)
						{
							pos1 = i;
							break;
						}
						else if (p->buf[i] == 0)
						{
							break;
						}
						i++;
					}
					else
					{
						break;
					}
				}
			}
		}
	}

	return pos1;
}

FUNCTION_INLINE ssize_t FUNC(find_whitespace)(T *p,
		size_t pos)
{
	ssize_t pos1 = -1;
	size_t i = 0;
	char ch = 0;

	if (p)
	{
		if (p->is_init &&
				p->buf &&
				p->read_pos < p->write_pos &&
				p->write_pos <= p->buf_size)
		{
			i = p->read_pos;
			while (i < p->write_pos)
			{
				ch = p->buf[i];
				if (CHAR_STRING_COMPARE_IS_WHITESPACE ||
						CHAR_STRING_COMPARE_IS_VERTICAL_WHITESPACE)
				{
					pos1 = i;
					break;
				}
				i++;
			}
		}
	}

	return pos1;
}

FUNCTION_INLINE ssize_t FUNC(find_chars)(T *p,
		size_t pos,
		const char *s,
		unsigned int flags)
{
	ssize_t pos1 = -1;
	char *s_pos = NULL;

	if (p &&
			s)
	{
		if (p->buf)
		{
			if (p->read_pos <= pos &&
					p->read_pos < p->write_pos &&
					p->write_pos <= p->buf_size)
			{
				s_pos = strstr(p->buf + pos,
						s);
				if (s_pos >= p->buf + pos)
				{
					pos1 = s_pos - p->buf;
				}
			}
		}
	}

	return pos1;
}

FUNCTION_INLINE ssize_t FUNC(find_string)(T *p,
		size_t pos,
		T *s,
		unsigned int flags)
{
	ssize_t pos1 = -1;
	int is_found = 0;
	const char *p_buf = NULL;
	const char *s_buf = NULL;
	const char *p_buf_max = NULL;
	const char *s_buf_max = NULL;

	if (p &&
			s)
	{
		if (p->buf &&
				p->read_pos < p->write_pos &&
				p->write_pos <= p->buf_size)
		{
			if (s->buf &&
					s->read_pos < s->write_pos &&
					s->write_pos <= s->buf_size)
			{
				if (pos >= p->read_pos &&
						pos < p->write_pos)
				{
					p_buf = p->buf + pos;
					s_buf = s->buf;
					p_buf_max = p->buf + p->write_pos;
					s_buf_max = s->buf + s->write_pos;
					while (1)
					{
						if (*p_buf == *s_buf)
						{
							if (!is_found)
							{
								is_found = 1;
								pos1 = p_buf - p->buf;
							}
							p_buf++;
							s_buf++;
							if ((*s_buf == 0 &&
										(flags & CHAR_STRING_FLAG_BINARY) == 0) ||
									s_buf >= s_buf_max)
							{
								break;
							}
							else
							{
								if ((*p_buf == 0 &&
										(flags & CHAR_STRING_FLAG_BINARY) == 0) ||
										p_buf >= p_buf_max)
								{
									is_found = 0;
									break;
								}
							}
						}
						else
						{
							if (is_found)
							{
								is_found = 0;
								s_buf = s->buf;
							}
							else
							{
								p_buf++;
								if ((*p_buf == 0 &&
										(flags & CHAR_STRING_FLAG_BINARY) == 0) ||
										p_buf >= p_buf_max)
								{
									break;
								}
							}
						}
					}
					if (is_found)
					{
						
					}
				}
			}
		}
	}

	return pos1;
}

FUNCTION_INLINE T* FUNC(replace_chars)(T *p,
		char *s,
		char *s_find,
		char *s_replace)
{	
	int is_set = 0;
	char *s1 = NULL;
	char *s2 = NULL;
	size_t size = 0;
	size_t s_find_size = 0;
	size_t s_replace_size = 0;

	if (s)
	{
		size = strlen(s);
		if (size)
		{
			if (s &&
					s_find &&
					s_replace)
			{
				s1 = s;
				s2 = s1;
				s_find_size = strlen(s_find);
				s_replace_size = strlen(s_replace);
				if (s_find_size)
				{
					while (s1 &&
							s2)
					{
						s2 = strstr(s1, s_find);
						if (s2)
						{
							// s_find is found
							if (s1 < s2)
							{
								// copy part before s_find
								p = char_string_read_char_size(p,
										s1,
										s2 - s1);
							}
							if (s_replace_size)
							{
								// s_replace is not empty
								p = FUNC(add_char)(p,
										s_replace,
										s_replace_size,
										0);
								if (p)
								{
								}
							}
							s1 = s2 + s_find_size;
							is_set++;
						}
						else
						{
							// copy part from s1
							p = char_string_read_char(p,
									s1);
						}
					}
				}
			}
		}
	}

	return p;
}

FUNCTION_INLINE int FUNC(skip_read_char)(T *p,
		const char *s,
		size_t s_size,
		unsigned int flags)
{
	int is_set = 0;
	char *s_pos = NULL;

	if (p &&
			s)
	{
		if (p->is_init &&
				p->buf &&
				p->read_pos < p->write_pos &&
				p->write_pos <= p->buf_size)
		{
			if (s_size == 0)
			{
				s_size = strlen(s);
			}
			if (s_size > 0)
			{
				if (flags & CHAR_STRING_FLAG_CURRENT)
				{
					is_set = strncmp(p->buf + p->read_pos,
							s,
							s_size);
					if (is_set)
					{
						is_set = 0;
					}
					else
					{
						p->read_pos += s_size;
						is_set = 1;
					}
				}
				else
				{
					s_pos = strstr(p->buf + p->read_pos,
							s);
					if (s_pos &&
							p->buf + p->read_pos < s_pos)
					{
						p->read_pos += s_size;
						is_set = 1;
					}
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(skip_read)(T *p,
		T *p_s,
		size_t s_size,
		unsigned int flags)
{
	int is_set = 0;

	if (p &&
			p_s)
	{
		if (p->is_init &&
				p_s->is_init)
		{
			if (p_s->buf &&
					p_s->read_pos < p_s->write_pos &&
					p_s->write_pos <= p_s->buf_size)
			{
				if (s_size == 0)
				{
					s_size = p_s->write_pos - p_s->read_pos;
				}
				is_set = FUNC(skip_read_char)(p,
						p_s->buf + p_s->read_pos,
						s_size,
						flags);
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(skip_read_whitespace)(T *p,
		unsigned int flags)
{
	int is_set = 0;
	size_t i = 0;
	char ch = 0;

	if (p)
	{
		if (p->is_init &&
				p->buf &&
				p->read_pos < p->write_pos &&
				p->write_pos <= p->buf_size)
		{
			if (flags & CHAR_STRING_FLAG_CURRENT)
			{
				i = p->read_pos;
			}
			else
			{
				i = p->read_pos;
				while (i < p->write_pos)
				{
					ch = p->buf[i];
					if (CHAR_STRING_COMPARE_IS_WHITESPACE ||
							CHAR_STRING_COMPARE_IS_VERTICAL_WHITESPACE)
					{
						break;
					}
					i++;
				}
			}
			while (i < p->write_pos)
			{
				ch = p->buf[i];
				if (CHAR_STRING_COMPARE_IS_WHITESPACE ||
						CHAR_STRING_COMPARE_IS_VERTICAL_WHITESPACE)
				{
				}
				else
				{
					p->read_pos = i;
					is_set = 1;
					break;
				}
				i++;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE T* FUNC(read_word_char_size_flags)(T *p,
		const char *s,
		size_t s_size,
		unsigned int flags)
{
//	int is_set = 0;

	p = FUNC(read_char_size_flags)(p,
			s,
			s_size,
			flags);
	if (p)
	{
//		is_set = 1;
	}

	return p;
}

FUNCTION_INLINE T* FUNC(copy_word)(T *p,
		T *p_s,
		size_t s_size,
		unsigned int flags)
{
//	int is_set = 0;
	size_t size = 0;
	ssize_t pos = 0;

	if (p_s)
	{
		if (p_s->buf &&
				p_s->read_pos < p_s->write_pos &&
				p_s->write_pos <= p_s->buf_size)
		{
			if (FUNC(skip_read_whitespace)(p_s,
						flags |
						CHAR_STRING_FLAG_CURRENT))
			{
			}
			pos = FUNC(find_whitespace)(p_s,
					0);
			if (pos >= 0)
			{
				size = pos - p_s->read_pos;
			}
			if (s_size &&
					s_size < size)
			{
				size = s_size;
			}
			p = FUNC(read_word_char_size_flags)(p,
					p_s->buf,
					size,
					flags);
		}
	}

	return p;
}

FUNCTION_INLINE int FUNC(check_slash)(T *p,
		unsigned int flags)
{
	int is_set = 0;

	if (p)
	{
		if (p->write_pos > 0)
		{
			if (p->buf[p->write_pos - 1] == '/')
			{
				is_set = 1;
			}
			else if (p->buf[p->write_pos - 1] == 0)
			{
				if (p->write_pos > 1)
				{
					if (p->buf[p->write_pos - 2] == '/')
					{
						is_set = 1;
					}
				}
			}
			if (!is_set &&
					(flags & CHAR_STRING_FLAG_ADD))
			{
				FUNC(add_char)(p,
						"/",
						1,
						0);
			}
		}
	}

	return is_set;
}

#undef MODULE_NAME

#include "module_undef.h"

#endif	/* CHAR_STRING_H */

