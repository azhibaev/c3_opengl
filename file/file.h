#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"
#include "char_string.h"

// module
// file
#define MODULE_NAME file

// struct
#define MODULE_STRUCT file_struct.h
#define MODULE_INIT file_init.h
#define MODULE_INIT_VAR file_init_var.h
#define MODULE_FREE file_free.h

#define FILE_FLAG_NEW_LINE	(1 << 0)

#include "module.h"

FUNCTION_INLINE int FUNC(read_line_flags)(T *p,
		unsigned int flags)
{
	int is_set = 0;
	ssize_t read_chars = 0;

	if (p)
	{
		if (p->f)
		{
			if (char_string_check_init(p->s))
			{
				char_string_reset(p->s);
				read_chars = getline(&p->s->buf,
						&p->s->buf_size,
						p->f);
				if (read_chars > 0)
				{
					if (!(flags & FILE_FLAG_NEW_LINE) &&
							p->s->buf[read_chars - 1] == '\n')
					{
						p->s->write_pos += read_chars - 1;
					}
					else
					{
						p->s->write_pos += read_chars;
					}
					p->read_chars = (size_t)read_chars;
					is_set = 1;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(read_line)(T *p)
{
	int is_set = 0;

	is_set = FUNC(read_line_flags)(p,
			0);

	return is_set;
}

FUNCTION_INLINE int FUNC(read_line_n)(T *p)
{
	int is_set = 0;

	is_set = FUNC(read_line_flags)(p,
			FILE_FLAG_NEW_LINE);

	return is_set;
}

FUNCTION_INLINE int FUNC(print)(T *p)
{
	int is_set = 0;

	if (p)
	{
		printf("%lx\n",
				(size_t)p->f);
		is_set = 1;
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(read)(T *p)
{
	int is_set = 0;

	if (p)
	{
		if (p->f)
		{
			if (char_string_check(p->s))
			{
				p->read_chars = fread(p->s->buf + p->s->write_pos,
						sizeof(char),
						p->s->buf_size - p->s->write_pos,
						p->f);
				if (p->read_chars > 0)
				{
					p->s->write_pos += p->read_chars;
					is_set = 1;
				}
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(write)(T *p)
{
	int is_set = 0;

	if (p)
	{
		if (p->f)
		{
			if (char_string_check(p->s))
			{
				p->write_chars = fwrite(p->s->buf + p->s->read_pos,
						sizeof(char),
						p->s->write_pos - p->s->read_pos,
						p->f);
				if (p->write_chars > 0)
				{
					p->s->read_pos += p->write_chars;
					is_set = 1;
				}
			}
		}
	}

	return is_set;
}

#undef MODULE_FREE
#undef MODULE_INIT
#undef MODULE_STRUCT
#undef MODULE_NAME

#include "module_undef.h"

#endif	/* FILE_H */
