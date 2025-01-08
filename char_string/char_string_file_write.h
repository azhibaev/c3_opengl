#ifndef CHAR_STRING_FILE_READ_H
#define CHAR_STRING_FILE_READ_H

FUNCTION_INLINE int FUNC(read_file)(T *p,
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

FUNCTION_INLINE int FUNC(read)(T *p)
{
	FILE *f = p->f;

	return FUNC(read_file)(p,
			f);
}

FUNCTION_INLINE T* FUNC(read_line_file)(T *p,
		FILE *f)
{
	if (f)
	{
		if (!p)
		{
			p = FUNC(create)(1);
		}
		if (p)
		{
			p->read_chars = getline(&p->buf, &p->buf_size, f);
			if (p->read_chars > 0 &&
					p->buf &&
					p->buf_size > 0)
			{
				p->is_init = 1;
				p->is_alloc = 1;
				p->read_pos = 0;
				p->write_pos = strlen(p->buf);
				if (p->write_pos > 1)
				{
					if (p->buf[p->write_pos - 1] == '\n')
					{
						p->write_pos--;
						p->buf[p->write_pos] = 0;
					}
				}
			}
		}
	}

	return p;
}

FUNCTION_INLINE T* FUNC(read_line)(T *p)
{
	FILE *f = p->f;

	return FUNC(read_line_file)(p,
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

#endif	/* CHAR_STRING_FILE_READ_H */

