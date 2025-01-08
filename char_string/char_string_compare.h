#ifndef CHAR_STRING_COMPARE_H
#define CHAR_STRING_COMPARE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"

#define CHAR_STRING_COMPARE_IS_ALPHA_UPPER (ch >= 'A' && ch <= 'Z')
#define CHAR_STRING_COMPARE_IS_ALPHA_LOWER (ch >= 'a' && ch <= 'z')
#define CHAR_STRING_COMPARE_IS_ALPHA (CHAR_STRING_COMPARE_IS_ALPHA_UPPER || \
		CHAR_STRING_COMPARE_IS_ALPHA_LOWER)
#define CHAR_STRING_COMPARE_IS_NUM (ch >= '0' && ch <= '9')
#define CHAR_STRING_COMPARE_IS_ALNUM (CHAR_STRING_COMPARE_IS_ALPHA || \
		CHAR_STRING_COMPARE_IS_NUM)
#define CHAR_STRING_COMPARE_IS_WHITESPACE (ch == ' ' || ch == '\t')
#define CHAR_STRING_COMPARE_IS_DASH (ch == '-')
#define CHAR_STRING_COMPARE_IS_DOT (ch == '.')
#define CHAR_STRING_COMPARE_IS_DOMAIN (CHAR_STRING_COMPARE_IS_ALNUM || \
		CHAR_STRING_COMPARE_IS_DASH || \
		CHAR_STRING_COMPARE_IS_DOT)
#define CHAR_STRING_COMPARE_IS_VERTICAL_WHITESPACE (ch == '\r' || ch == '\n')
#define CHAR_STRING_COMPARE_IS_UNDERLINE (ch == '_')
#define CHAR_STRING_COMPARE_IS_IDENTIFIER (CHAR_STRING_COMPARE_IS_ALNUM || \
		CHAR_STRING_COMPARE_IS_UNDERLINE)

#define MODULE_NAME char_string_compare

#define MODULE_STRUCT		char_string_compare_struct.h

#include "module.h"

FUNCTION_INLINE int FUNC(line)(T *p,
		const char *s)
{
	int is_set = 0;
	size_t i = 0;

	if (p && s)
	{
		for (i = p->pos1; i < p->pos2; i++)
		{
			if (s[i] == '\r' ||
					s[i] == '\n' ||
					s[i] == '\0')
			{
				p->pos2 = i;
				is_set = 1;
				break;
			}
		}
		if (is_set == 0 &&
				i == p->pos2)
		{
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(trim)(T *p,
		const char *s)
{
	int is_set = 0;
	size_t i = 0;

	if (p && s)
	{
		for (i = p->pos1; i < p->pos2; i++)
		{
			if (s[i] != ' ' &&
					s[i] != '\t')
			{
				p->pos1 = i;
				is_set = 1;
				break;
			}
		}
		if (p->pos2 > 0)
		{
			for (i = p->pos2 - 1; i >= p->pos1; i--)
			{
				if (s[i] != ' ' &&
						s[i] != '\t')
				{
					p->pos2 = i + 1;
					is_set = 1;
					break;
				}
			}
		}
	}

	return is_set;
}

/* Return: reset flags on error */
FUNCTION_INLINE int FUNC(alnum)(T *p,
		const char *s,
		unsigned int flags)
{
	size_t i = 0;
	char ch = 0;
	unsigned int flags_alnum = 0;

	if (p && s)
	{
		flags_alnum = flags & CHAR_STRING_FLAG_ALNUM;
		if (flags_alnum == CHAR_STRING_FLAG_ALNUM)
		{
			for (i = p->pos1; i < p->pos2; i++)
			{
				ch = s[i];
				if (CHAR_STRING_COMPARE_IS_ALNUM)
				{
				}
				else
				{
					if (flags & CHAR_STRING_FLAG_WHITESPACE)
					{
						if (CHAR_STRING_FLAG_WHITESPACE)
						{
							continue;
						}
					}
					p->pos2 = i;
					flags_alnum ^= CHAR_STRING_FLAG_ALNUM;
					break;
				}
			}
		}
		else if (flags_alnum == CHAR_STRING_FLAG_ALPHA)
		{
			for (i = p->pos1; i < p->pos2; i++)
			{
				ch = s[i];
				if (CHAR_STRING_COMPARE_IS_ALPHA)
				{
				}
				else
				{
					if (flags & CHAR_STRING_FLAG_WHITESPACE)
					{
						if (CHAR_STRING_FLAG_WHITESPACE)
						{
							continue;
						}
					}
					p->pos2 = i;
					flags_alnum ^= CHAR_STRING_FLAG_ALPHA;
					break;
				}
			}
		}
		else if (flags_alnum & CHAR_STRING_FLAG_ALNUM)
		{
			for (i = p->pos1; i < p->pos2; i++)
			{
				ch = s[i];
				if (flags_alnum & CHAR_STRING_FLAG_ALPHA_UPPER)
				{
					if (CHAR_STRING_COMPARE_IS_ALPHA_UPPER)
					{
					}
					else
					{
						if (flags & CHAR_STRING_FLAG_WHITESPACE)
						{
							if (CHAR_STRING_FLAG_WHITESPACE)
							{
							}
							else
							{
								p->pos2 = i;
								flags_alnum ^= CHAR_STRING_FLAG_ALPHA_UPPER;
								break;
							}
						}
						p->pos2 = i;
						flags_alnum ^= CHAR_STRING_FLAG_ALPHA_UPPER;
						break;
					}
				}
				if (flags_alnum & CHAR_STRING_FLAG_ALPHA_LOWER)
				{
					if (CHAR_STRING_COMPARE_IS_ALPHA_LOWER)
					{
					}
					else
					{
						if (flags & CHAR_STRING_FLAG_WHITESPACE)
						{
							if (CHAR_STRING_FLAG_WHITESPACE)
							{
							}
							else
							{
								p->pos2 = i;
								flags_alnum ^= CHAR_STRING_FLAG_ALPHA_LOWER;
								break;
							}
						}
						p->pos2 = i;
						flags_alnum ^= CHAR_STRING_FLAG_ALPHA_LOWER;
						break;
					}
				}
				if (flags_alnum & CHAR_STRING_FLAG_NUM)
				{
					if (CHAR_STRING_COMPARE_IS_NUM)
					{
					}
					else
					{
						if (flags & CHAR_STRING_FLAG_WHITESPACE)
						{
							if (CHAR_STRING_FLAG_WHITESPACE)
							{
							}
							else
							{
								p->pos2 = i;
								flags_alnum ^= CHAR_STRING_FLAG_NUM;
								break;
							}
						}
						p->pos2 = i;
						flags_alnum ^= CHAR_STRING_FLAG_NUM;
						break;
					}
				}
			}
		}
	}

	return flags_alnum;
}

/* Return: reset flags on error */
FUNCTION_INLINE int FUNC(domain)(T *p,
		const char *s,
		unsigned int flags)
{
	size_t i = 0;
	char ch = 0;
	unsigned int flags_alnum = 0;

	if (p && s)
	{
		flags_alnum = flags & CHAR_STRING_FLAG_DOMAIN;
		if (flags_alnum == CHAR_STRING_FLAG_DOMAIN)
		{
			for (i = p->pos1; i < p->pos2; i++)
			{
				ch = s[i];
				if (CHAR_STRING_COMPARE_IS_DOMAIN)
				{
				}
				else
				{
					p->pos2 = i;
					flags_alnum ^= CHAR_STRING_FLAG_DOMAIN;
					break;
				}
			}
		}
	}

	return flags_alnum;
}

/* Return: reset flags on error */
FUNCTION_INLINE int FUNC(identifier)(T *p,
		const char *s,
		unsigned int flags)
{
	size_t i = 0;
	char ch = 0;
	unsigned int flags_alnum = 0;

	if (p && s)
	{
		flags_alnum = flags & CHAR_STRING_FLAG_IDENTIFIER;
		if (flags_alnum == CHAR_STRING_FLAG_IDENTIFIER)
		{
			for (i = p->pos1; i < p->pos2; i++)
			{
				ch = s[i];
				if (CHAR_STRING_COMPARE_IS_IDENTIFIER)
				{
				}
				else
				{
					p->pos2 = i;
					flags_alnum ^= CHAR_STRING_FLAG_IDENTIFIER;
					break;
				}
			}
		}
	}

	return flags_alnum;
}

FUNCTION_INLINE unsigned int FUNC(check)(T *p,
		const char *s,
		unsigned int flags)
{
	unsigned int is_set = 0;

	if (p && s)
	{
		if (flags & CHAR_STRING_FLAG_LINE)
		{
			if (FUNC(line)(p, s))
			{
				is_set |= CHAR_STRING_FLAG_LINE;
			}
		}

		if (flags & CHAR_STRING_FLAG_TRIM)
		{
			if (FUNC(trim)(p, s))
			{
				is_set |= CHAR_STRING_FLAG_TRIM;
			}
		}

		if (flags & CHAR_STRING_FLAG_ALNUM)
		{
			is_set |= FUNC(alnum)(p, s, flags);
		}

		if (flags & CHAR_STRING_FLAG_DOMAIN)
		{
			is_set |= FUNC(domain)(p, s, flags);
		}

		if (flags & CHAR_STRING_FLAG_IDENTIFIER)
		{
			is_set |= FUNC(identifier)(p, s, flags);
		}
	}

	return is_set;
}

#undef MODULE_NAME

#include "module_undef.h"

#endif	/* CHAR_STRING_COMPARE_H */

