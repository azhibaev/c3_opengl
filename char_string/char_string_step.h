#ifndef CHAR_STRING_STEP_H
#define CHAR_STRING_STEP_H

FUNCTION_INLINE size_t FUNC(step_next)(T *p)
{
	int is_set = 0;

	if (FUNC(check)(p))
	{
		if (p->read_pos + 1 < p->write_pos)
		{
			p->read_pos++;
			is_set = 1;
		}
	}

	return is_set;
}

FUNCTION_INLINE size_t FUNC(step_prev)(T *p)
{
	int is_set = 0;

	if (FUNC(check)(p))
	{
		if (p->read_pos > 0)
		{
			p->read_pos--;
			is_set = 1;
		}
	}

	return is_set;
}

#endif	/* CHAR_STRING_STEP_H */

