#ifndef CHAR_STRING_WRITE_CHAR_H
#define CHAR_STRING_WRITE_CHAR_H

FUNCTION_INLINE T* FUNC(write_char_size_flags)(T *p,
		const char *s,
		size_t size,
		unsigned int flags)
{
	T_NAME(compare) s_cmp = {0};
	unsigned int is_set = 0;

	if (s)
	{
		if (size == 0)
		{
			size = strlen(s);
		}

		if (size > 0)
		{
			s_cmp.pos1 = 0;
			s_cmp.pos2 = size;

			is_set = FUNC(compare_check)(&s_cmp, s, flags);

			if (is_set ||
					(flags &
					 (CHAR_STRING_FLAG_LINE |
					  CHAR_STRING_FLAG_TRIM |
					  CHAR_STRING_FLAG_ALNUM |
					  CHAR_STRING_FLAG_DOMAIN |
					  CHAR_STRING_FLAG_IDENTIFIER)) == 0)
			{
				if (s_cmp.pos2 > s_cmp.pos1)
				{
					size = s_cmp.pos2 - s_cmp.pos1;
					p = FUNC(realloc)(p, size, flags);
					if (p)
					{
						if ((flags & CHAR_STRING_FLAG_ADD) == 0)
						{
							FUNC(reset)(p);
						}
						if (p->write_pos + size < p->buf_size)
						{
							memcpy(p->buf + p->write_pos, s + s_cmp.pos1, size);
							p->write_pos += s_cmp.pos2 - s_cmp.pos1;
							p->buf[p->write_pos] = 0;
						}
					}
				}
				else if (is_set | CHAR_STRING_FLAG_LINE)
				{
					p = FUNC(realloc)(p, 10, 0);
				}
			}
			else
			{
				if ((flags & CHAR_STRING_FLAG_ADD) == 0)
				{
					FUNC(reset)(p);
				}
			}
		}
	}

	return p;
}

FUNCTION_INLINE T* FUNC(write_char)(T *p,
		const char *s)
{
	size_t size = 0;
	unsigned int flags = 0;

	return FUNC(write_char_size_flags)(p,
			s,
			size,
			flags);
}

FUNCTION_INLINE T* FUNC(write_char_size)(T *p,
		const char *s,
		size_t size)
{
	unsigned int flags = 0;

	return FUNC(write_char_size_flags)(p,
			s,
			size,
			flags);
}

FUNCTION_INLINE T* FUNC(write_char_flags)(T *p,
		const char *s,
		unsigned int flags)
{
	size_t size = 0;

	return FUNC(write_char_size_flags)(p,
			s,
			size,
			flags);
}

FUNCTION_INLINE T* FUNC(write_const_char)(T *p,
		const char *s,
		size_t s_size,
		unsigned int flags)
{
	if (s)
	{
		if (s_size == 0)
		{
			s_size = strlen(s);
			if (!p)
			{
				p = FUNC(create)(1);
			}
			if (p)
			{
				if (p->is_alloc == 0)
				{
					p->buf = (char*)s;
				}
				else
				{
					p = FUNC(realloc)(p, s_size, 0);
					memcpy(p->buf, s, s_size);
					p->write_pos = s_size;
					p->buf[p->write_pos] = 0;
				}
				p->is_init = 1;
			}
		}
		else
		{
			p = FUNC(realloc)(p, s_size, 0);
			if (p)
			{
				memcpy(p->buf, s, s_size);
				p->write_pos = s_size;
				p->buf[p->write_pos] = 0;
				p->is_init = 1;
			}
		}
	}

	return p;
}

#endif	/* CHAR_STRING_WRITE_CHAR_H */

