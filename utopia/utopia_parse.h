#ifndef UTOPIA_PARSE
#define UTOPIA_PARSE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"
#include "char_string.h"
#include "parse.h"
#include "file.h"

// module
// utopia_parse
#define MODULE_NAME utopia_parse

// struct
#define MODULE_STRUCT utopia_parse_struct.h
#define MODULE_INIT utopia_parse_init.h
#define MODULE_INIT_VAR utopia_parse_init_var.h
#define MODULE_FUNC_DEF utopia_parse_func_def.h
#define UTOPIA_PARSE_SECTION_LIST "utopia_parse_section_list.h"

#include "module.h"

enum utopia_parse_section_name_e
{
#define ITEM(s) ARRAY_INDEX_E(s),
#define ITEM_2(s,i) ARRAY_INDEX_I_E(#s,i),
#include UTOPIA_PARSE_SECTION_LIST
#undef ITEM
#undef ITEM_2
};

struct array_index utopia_parse_section_name_a[] =
{
#define ITEM(s) ARRAY_INDEX(s),
#define ITEM_2(s,i) ARRAY_INDEX_I(#s,i),
#include UTOPIA_PARSE_SECTION_LIST
#undef ITEM
#undef ITEM_2
};

#include "section_module.h"
#include "section_struct.h"
#include "section_init.h"
#include "section_free.h"

FUNCTION_INLINE int FUNC(find_array)(char_string *s,
		array_index *a,
		size_t a_size)
{
	int is_set = 0;
	size_t s_size = 0;
	size_t i = 0;

	if (char_string_check(s))
	{
		s_size = s->write_pos - s->read_pos;
		for (i = 0; i < a_size; i++)
		{
			if (s_size >= a[i].size)
			{
				if (!strncmp(s->buf + s->read_pos,
							a[i].s,
							a[i].size))
				{
					s->read_pos += a[i].size;
					is_set = 1;
					break;
				}
			}
		}
	}

	return is_set ? a[i].index : -1;
}

FUNCTION_INLINE int FUNC(section_name)(char_string *s)
{
	int is_set = 0;

	is_set = FUNC(find_array)(s,
			T_NAME(section_name_a),
			ARRAY_INDEX_SIZE(T_NAME(section_name_a)));

	return is_set;
}

FUNCTION_INLINE int FUNC(state)(T *p)
{
	int is_set = 0;

	if (p)
	{
		if (p->is_module)
		{
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(section)(T *p,
		char_string *s)
{
	int is_set = 0;

	if (p)
	{
		if (parse_hash(s))
		{
			p->section_index = FUNC(section_name)(s);
			if (p->section_index >= 0)
			{
				is_set = 1;
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(write_out)(T *p)
{
	int is_set = 0;

	if (p)
	{
		is_set = 1;
		if (!p->f_out->f)
		{
			if (p->is_module)
			{
				p->s = char_string_copy(p->s,
						p->s_path_out);
				p->s = char_string_add_char(p->s,
						"/",
						0,
						0);
				p->s = char_string_add(p->s,
						p->s_module,
						0);
				p->s = char_string_add_char(p->s,
						".h",
						0,
						0);
				if (file_init(p->f_out,
						p->s->buf,
						"w"))
				{
					p->s_out = char_string_add(p->s_out,
							p->f_in->s,
							0);
					p->f_out->s = char_string_copy(p->f_out->s,
							p->s_out);
				}
				else
				{
					return is_set;
				}
			}
			else
			{
				p->s_out = char_string_add(p->s_out,
						p->f_in->s,
						0);
				return is_set;
			}
		}
		else
		{
			p->f_out->s = char_string_copy(p->f_out->s,
					p->f_in->s);
		}
		file_write(p->f_out);
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(run)(T *p)
{
	int is_set = 0;

	if (p)
	{
		while (file_read_line(p->f_in))
		{
			is_set = FUNC(section)(p,
					p->f_in->s);
			if (is_set)
			{
				switch (p->section_index)
				{
#define ITEM(s_i) case (s_i ## _index): \
					{ \
						is_set = FUNC(section_ ## s_i)(p); \
						break; \
					}
#define ITEM_2(s,i) ITEM(i)
#include UTOPIA_PARSE_SECTION_LIST
#undef ITEM
#undef ITEM_2
					default:
						{
							break;
						}
				}
			}
			else
			{
				char_string_reset_read(p->f_in->s);
				char_string_reset_write_new_line(p->f_in->s);
				FUNC(write_out)(p);
			}
		}
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(open_file)(T *p,
		char *file_name,
		char *s_options)
{
	int is_set = 0;

	if (p)
	{
		if (file_name)
		{
			p->s = char_string_copy(p->s,
					p->s_path_out);
			p->s = char_string_add_char(p->s,
					"/",
					0,
					0);
			if (char_string_check(p->s_module))
			{
				p->s = char_string_add(p->s,
						p->s_module,
						0);
				p->s = char_string_add_char(p->s,
						"_",
						0,
						0);
			}
			p->s = char_string_add_char(p->s,
					file_name,
					0,
					0);
			file_init(p->f_section,
					p->s->buf,
					s_options);
			is_set++;
		}
	}

	return is_set;
}

#undef UTOPIA_PARSE_SECTION_LIST

#include "module_undef.h"

#endif	/* UTOPIA_PARSE */

