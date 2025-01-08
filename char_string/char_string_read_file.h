#ifndef CHAR_STRING_FILE_READ_H
#define CHAR_STRING_FILE_READ_H

FUNCTION_INLINE size_t FUNC(read_file)(T *p,
		FILE *f)
{
	return FUNC(file_read_file_static)(p,
				f);
}

FUNCTION_INLINE T* FUNC(read_line_file)(T *p,
		FILE *f)
{
	if (f)
	{
		if (!p)
		{
			p = FUNC(init)(p,
					0);
		}
		if (FUNC(file_read_line_file_static)(p,
					f))
		{
		}
	}

	return p;
}

#endif	/* CHAR_STRING_FILE_READ_H */

