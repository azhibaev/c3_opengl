#ifndef CHAR_STRING_FILE_H
#define CHAR_STRING_FILE_H

#include "char_string.h"

#define MODULE_NAME char_string_file

#define MODULE_STRUCT				char_string_file_struct.h

#include "module.h"

FUNCTION_INLINE int FUNC(read_file)(T *p,
		char_string *p_s,
		FILE *f)
{
	int is_read = 0;

	if (p && p_s && f)
	{
		p->read_chars = fread(p_s->buf + p_s->write_pos, 
				sizeof(char), 
				p_s->buf_size - p_s->write_pos, 
				f);
		if (p->read_chars)
		{
			is_read = 1;
		}
		p_s->read_pos = p_s->write_pos;
		p_s->write_pos += p->read_chars;
		/* 0: EOF or Error */
	}

	return is_read;
}

FUNCTION_INLINE int FUNC(read)(T *p,
		char_string *p_s)
{
	FILE *f = p->f;

	return FUNC(read_file)(p,
			p_s,
			f);
}

FUNCTION_INLINE size_t FUNC(read_file_static)(char_string *p_s,
		FILE *f)
{
	char_string_file s_f = {0};

	if (FUNC(read_file)(&s_f,
			p_s,
			f))
	{
		return s_f.read_bytes;
	}

	return 0;
}

FUNCTION_INLINE T* FUNC(read_line_file)(T *p,
		char_string *p_s,
		FILE *f)
{
	if (p && p_s && f)
	{
		p->read_chars = getline(&p_s->buf, &p_s->buf_size, f);
		if (p->read_chars > 0 &&
				p_s->buf &&
				p_s->buf_size > 0)
		{
			p_s->read_pos = 0;
			p_s->write_pos = strlen(p_s->buf);
			if (p_s->write_pos > 1)
			{
				if (p_s->buf[p_s->write_pos - 1] == '\n')
				{
					p_s->write_pos--;
					p_s->buf[p_s->write_pos] = 0;
				}
			}
		}
	}

	return p;
}

FUNCTION_INLINE T* FUNC(read_line)(T *p,
		char_string *p_s)
{
	FILE *f = p->f;

	return FUNC(read_line_file)(p,
			p_s,
			f);
}

FUNCTION_INLINE T* FUNC(read_line_file_static)(char_string *p_s,
		FILE *f)
{
	char_string_file s_f = {0};

	return FUNC(read_line_file)(&s_f,
			p_s,
			f);
}

FUNCTION_INLINE int FUNC(write)(T *p,
		char_string *p_s,
		FILE *f)
{
	int is_write = 0;

	if (p && p_s && f)
	{
		if (p_s->buf &&
				p_s->read_pos < p_s->write_pos &&
				p_s->write_pos <= p_s->buf_size)
		{
			p->write_chars = fwrite(p_s->buf + p_s->read_pos, 
					sizeof(char), 
					p_s->write_pos - p_s->read_pos, 
					f);
			if (p->write_chars)
			{
				is_write = 1;
				p_s->read_pos += p->write_chars;
			}
			/* 0: Error */
		}
	}

	return is_write;
}

#undef MODULE_NAME

#include "module_undef.h"

#endif	/* CHAR_STRING_FILE_H */

