#ifndef SECTION_MODULE_H
#define SECTION_MODULE_H

FUNCTION_INLINE int FUNC(section_module)(T *p)
{
	int is_set = 0;

	if (p)
	{
		if (p->f_in)
		{
			if (char_string_check(p->f_in->s))
			{
				if (parse_lws(p->f_in->s))
				{
				}
				p->s_module = char_string_copy(p->s_module,
						p->f_in->s);
				p->is_module = 1;
				p->f_in->s = char_string_read_char(p->f_in->s,
						"#define MODULE_NAME ");
				p->f_in->s = char_string_add(p->f_in->s,
						p->s_module,
						0);
				p->f_in->s = char_string_add_char(p->f_in->s,
						"\n",
						0,
						0);
				is_set = FUNC(write_out)(p);
			}
		}
	}

	return is_set;
}

#endif	/* SECTION_MODULE_H */

