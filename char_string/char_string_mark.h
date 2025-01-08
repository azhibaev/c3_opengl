#ifndef CHAR_STRING_MARK_H
#define CHAR_STRING_MARK_H

FUNCTION_INLINE size_t FUNC(mark_get_read)(T *p)
{
	size_t i_mark = 0;

	if (FUNC(check_init)(p))
	{
		i_mark = p->read_pos;
	}

	return i_mark;
}

FUNCTION_INLINE int FUNC(mark_set_read)(T *p,
		size_t i_mark)
{
	int is_set = 0;

	if (FUNC(check_init)(p))
	{
		if (i_mark <= p->write_pos)
		{
			p->read_pos = i_mark;
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE size_t FUNC(mark_get_write)(T *p)
{
	size_t i_mark = 0;

	if (FUNC(check_init)(p))
	{
		i_mark = p->write_pos;
	}

	return i_mark;
}

FUNCTION_INLINE int FUNC(mark_set_write)(T *p,
		size_t i_mark)
{
	int is_set = 0;

	if (FUNC(check_init)(p))
	{
		if (i_mark <= p->buf_size)
		{
			p->read_pos = 0;
			p->write_pos = i_mark;
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(write_mark)(T *p,
		T *s,
		size_t i_mark)
{
	int is_set = 0;
	size_t pos = 0;

	if (FUNC(check_init)(p))
	{
		if (s)
		{
			pos = FUNC(mark_get_read)(p);
			if (i_mark < pos)
			{
				if (FUNC(mark_set_read)(p,
							i_mark))
				{
					if (FUNC(copy_size)(s,
								p,
								pos - i_mark))
					{
						if (FUNC(mark_set_read)(p,
									pos))
						{
							is_set = 1;
						}
					}
				}
			}
		}
	}

	return is_set;
}

#endif	/* CHAR_STRING_MARK_H */

