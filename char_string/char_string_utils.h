#ifndef CHAR_STRING_UTILS_H
#define CHAR_STRING_UTILS_H

FUNCTION_INLINE int FUNC(reset)(T *p)
{
	int is_set = 0;

	if (p)
	{
		p->read_pos = 0;
		p->write_pos = 0;
		is_set = 1;
	}

	return is_set;
}

FUNCTION_INLINE T* FUNC(reset_init)(T *p)
{
	if (p)
	{
		FUNC(reset)(p);
	}
	else
	{
		p = FUNC(create_init)(1,
				0);
	}

	return p;
}

FUNCTION_INLINE int FUNC(reset_read)(T *p)
{
	int is_set = 0;

	if (p)
	{
		p->read_pos = 0;
		is_set = 1;
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(reset_write_new_line)(T *p)
{
	int is_set = 0;

	if (FUNC(check)(p))
	{
		if (p->buf[p->write_pos] == '\n' &&
				p->write_pos < p->buf_size)
		{
			p->write_pos++;
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(skip_write_new_line)(T *p)
{
	int is_set = 0;

	if (FUNC(check)(p))
	{
		if (p->buf[p->write_pos - 1] == '\n')
		{
			p->write_pos--;
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(clear)(T *p)
{
	int is_set = 0;

	if (p)
	{
		if (FUNC(reset)(p))
		{
			if (p->is_init)
			{
				if (p->is_alloc)
				{
					if (p->buf &&
							p->buf_size > 0)
					{
						memset(p->buf, 0, p->buf_size);
					}
				}
			}
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE T* FUNC(realloc)(T *p,
		size_t size,
		unsigned int flags)
{
	char *buf = NULL;
	size_t buf_size = 0;
	int is_alloc = 0;
	int is_free_buf = 0;
	double size_factor = 0;

	if (!p)
	{
		if (size)
		{
			p = FUNC(create_init)(1, size);
		}
		else
		{
			p = FUNC(create)(1);
		}
	}
	if (p)
	{
		if (p->is_init == 0 ||
				p->buf == NULL)
		{
			FUNC(init)(p,
			size);
		}
		else
		{
			if (flags & CHAR_STRING_FLAG_ADD)
			{
				buf_size = p->write_pos;
				buf = p->buf;
				if (buf_size > 0)
				{
					size += buf_size;
				}
			}
			if (p->is_alloc == 0)
			{
				if (buf)
				{
					is_alloc = 1;
				}
			}
			else
			{
				if (p->buf_size < size + 1)
				{
					is_alloc = 1;
				}
			}
		}

		if (p &&
				is_alloc)
		{
			if (buf == NULL)
			{
				buf = p->buf;
				is_free_buf = 1;
			}

			if (p->factor > 0)
			{
				size_factor = ceil(p->buf_size * p->factor);
				if (size_factor > 0)
				{
					if (size < size_factor)
					{
						size = (size_t) size_factor;
					}
				}
			}
			FUNC(init)(p, size);

			if (is_free_buf)
			{
				free(buf);
			}
			else if (buf)
			{
				if (p->write_pos + buf_size < p->buf_size)
				{
					memcpy(p->buf + p->write_pos, buf, buf_size);
					p->write_pos += buf_size;
					p->buf[p->write_pos] = 0;
					free(buf);
				}
			}
		}
	}

	return p;
}


#endif	/* CHAR_STRING_UTILS_H */
