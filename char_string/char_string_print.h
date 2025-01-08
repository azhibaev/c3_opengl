#ifndef CHAR_STRING_PRINT_H
#define CHAR_STRING_PRINT_H

FUNCTION_INLINE int FUNC(print)(T *p)
{
	int is_set = 0;

	if (p)
	{
		if (FUNC(check(p)))
		{
			printf("%s\n",
					p->buf + p->read_pos);
			is_set = 1;
		}
	}

	return is_set;
}

#endif	/* CHAR_STRING_PRINT_H */

