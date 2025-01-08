#ifndef CHAR_STRING_CRYPT_H
#define CHAR_STRING_CRYPT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <crypt.h>

#include "common_def.h"

#include "char_string.h"
#include "char_string_compare.h"
#include "char_string_random.h"

#define CHAR_STRING_CRYPT_SALT_SHA256 "$5$"
#define CHAR_STRING_CRYPT_SALT_SHA512 "$6$"
#define CHAR_STRING_CRYPT_SALT_YESCRYPT "$y$j9T$"

#define MODULE_NAME char_string_crypt

#define MODULE_INIT					char_string_crypt_init.h

#include "module.h"

FUNCTION_INLINE char_string* FUNC(gensalt)(char_string *p,
		const char *s)
{
	char_string_reset(p);
	if (s == NULL)
	{
		s = CHAR_STRING_CRYPT_SALT_SHA512;
	}
	p = char_string_copy_char(p,
			s,
			0,
			0);
	p = char_string_random_get(p,
			16,
			16,
			CHAR_STRING_FLAG_ADD);
	
	return p;
}

FUNCTION_INLINE int FUNC(hash_char)(T *p,
		const char *s)
{
	int is_set = 0;
	char *s_hash = NULL;
	char *s_salt = NULL;
	char_string *p_salt = NULL;

	if (p &&
			s)
	{
		char_string_reset(p->s_hash);
		if (p->s_salt)
		{
			if (p->s_salt->buf &&
					p->s_salt->read_pos < p->s_salt->write_pos &&
					p->s_salt->write_pos <= p->s_salt->buf_size)
			{
				if (p->s_salt->buf[p->s_salt->write_pos] == 0)
				{
					s_salt = p->s_salt->buf + p->s_salt->read_pos;
				}
				else
				{
					p_salt = char_string_copy(p_salt,
							p->s_salt,
							0,
							0);
					if (p_salt)
					{
						s_salt = p_salt->buf;
					}
				}

				if (s_salt)
				{
					printf("Salt: %s\n", s_salt);
					s_hash = crypt(s,
							s_salt);
					printf("Hash: %s\n", s_hash);
					if (s_hash)
					{
						if (char_string_copy_char(p->s_hash,
									s_hash,
									0,
									0))
						{
							is_set = 1;
						}
					}
				}
				if (p_salt)
				{
					char_string_free(p_salt);
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(hash)(T *p,
		char_string *s)
{
	int is_set = 0;
	char_string *p_s = NULL;

	if (p &&
			s)
	{
		if (p->s_salt)
		{
			if (s->buf &&
					s->read_pos < s->write_pos &&
					s->write_pos <= s->buf_size)
			{
				if (p->s_salt->buf &&
						p->s_salt->read_pos < p->s_salt->write_pos &&
						p->s_salt->write_pos <= p->s_salt->buf_size)
				{
					if (s->buf[s->write_pos] == 0)
					{
						is_set = FUNC(hash_char)(p,
								s->buf + s->read_pos);
					}
					else
					{
						p_s = char_string_copy(p_s,
								s,
								0,
								0);
						is_set = FUNC(hash_char)(p,
								p_s->buf);
						char_string_free(p_s);
					}
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(get_salt)(T *p,
		char_string *p_buffer,
		size_t pos1,
		size_t pos2)
{
	int is_get = 0;
	size_t i = 0;
	size_t salt_pos1 = 0;
	size_t salt_pos2 = 0;

	if (p &&
			pos1 < pos2)
	{
		salt_pos1 = char_string_find_char(p_buffer, pos1 ? pos1 + 1 : 0, '$');
		if (salt_pos1 == (pos1 ? pos1 + 1 : 0) &&
				salt_pos1 < pos2)
		{
			salt_pos2 = salt_pos1;
			while (1)
			{
				i = char_string_find_char(p_buffer, salt_pos2 + 1, '$');
				if (i > pos1 &&
						i < pos2)
				{
					salt_pos2 = i;
				}
				else
				{
					break;
				}
			}
			if (salt_pos1 < salt_pos2)
			{
				p->s_salt = char_string_copy_char(p->s_salt,
						p_buffer->buf + salt_pos1,
						salt_pos2 - salt_pos1,
						0);
				if (p->s_salt)
				{
					p->s_hash = char_string_copy_char(p->s_hash,
							p_buffer->buf + salt_pos1,
							pos2 - salt_pos1,
							0);
					if (p->s_hash)
					{
						is_get = 1;
					}
				}
			}
		}
	}

	return is_get;
}

FUNCTION_INLINE int FUNC(get_salt_shadow)(T *p,
		char_string *p_buffer)
{
	int is_get = 0;
	size_t pos1 = 0;
	size_t pos2 = 0;

	if (p)
	{
		pos1 = char_string_find_char(p_buffer, 0, ':');
		pos2 = char_string_find_char(p_buffer, pos1 + 1, ':');
		is_get = FUNC(get_salt)(p,
				p_buffer,
				pos1,
				pos2);
	}

	return is_get;
}

#undef MODULE_INIT
#undef MODULE_NAME

#include "module_undef.h"

#endif	/* CHAR_STRING_CRYPT_H */

