#ifndef CHAR_STRING_SOCKET_H
#define CHAR_STRING_SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "common_def.h"

#include "char_string.h"

#define MODULE_NAME char_string_socket

#include "module.h"

FUNCTION_INLINE int FUNC(read)(T *p,
		int socket,
		char_string *p_s)
{
	int is_read = 0;

	if (p && socket && p_s)
	{
		if (p_s->buf &&
				p_s->write_pos < p_s->buf_size)
		{
			p->read_chars = read(socket, 
					p_s->buf + p_s->write_pos, 
					p_s->buf_size - p_s->write_pos);
			if (p->read_chars > 0)
			{
				p_s->read_pos = p_s->write_pos;
				p_s->write_pos += p->read_chars;
				is_read = 1;
			}
			/*  0: EOF
			 * -1: Error */
		}
	}

	return is_read;
}

FUNCTION_INLINE int FUNC(write)(T *p,
		int socket,
		char_string *p_s)
{
	int is_write = 0;

	if (p && socket && p_s)
	{
		if (p_s->write_pos > p_s->read_pos &&
				p_s->write_pos <= p_s->buf_size)
		{
			p->write_chars = write(socket, 
					p_s->buf + p_s->read_pos, 
					p_s->write_pos - p_s->read_pos);
			if (p->write_chars > 0)
			{
				is_write = 1;
				p_s->read_pos += p->write_chars;
			}
			/*  0: No write
			 * -1: Error */
		}
	}

	return is_write;
}

#undef MODULE_NAME

#include "module_undef.h"

#endif	/* CHAR_STRING_SOCKET_H */

