#ifndef SECTION_STRUCT_H
#define SECTION_STRUCT_H

#define SECTION_STRUCT_FILE_NAME "struct.h"

FUNCTION_INLINE int FUNC(section_struct)(T *p)
{
	int is_set = 0;
	size_t pos = 0;
	int is_create = 0;
	int is_init = 0;
	int is_free = 0;
	int is_pointer = 0;
	int is_var_type = 0;
	size_t pos_var = 0;
	size_t pos_var_type = 0;

	if (p)
	{
		if (p->f_in)
		{
			p->s_struct = char_string_reset_init(p->s_struct);
			p->s_struct_flags = char_string_reset_init(p->s_struct_flags);
			while (file_read_line(p->f_in))
			{
				if (char_string_check(p->f_in->s))
				{
					if (parse_lws(p->f_in->s))
					{
					}
					pos = p->f_in->s->read_pos;
					// "free" ? ->
					if (parse_identifier(p->f_in->s))
					{
						if (!strncmp(p->f_in->s->buf + pos,
									"create",
									p->f_in->s->read_pos - pos))
						{
							if (parse_get_char(p->f_in->s) == ';' ||
									p->f_in->s->read_pos + 1 >= p->f_in->s->write_pos)
							{
								is_var_type = 1;
							}
							else
							{
								is_create = 1;
								if (parse_lws(p->f_in->s))
								{
								}
								pos = p->f_in->s->read_pos;
								if (parse_identifier(p->f_in->s))
								{
									is_var_type = 1;
								}
							}
						}
						else if (!strncmp(p->f_in->s->buf + pos,
									"init",
									p->f_in->s->read_pos - pos))
						{
							if (parse_get_char(p->f_in->s) == ';' ||
									p->f_in->s->read_pos + 1 >= p->f_in->s->write_pos)
							{
								is_var_type = 1;
							}
							else
							{
								is_init = 1;
								if (parse_lws(p->f_in->s))
								{
								}
								pos = p->f_in->s->read_pos;
								if (parse_identifier(p->f_in->s))
								{
									is_var_type = 1;
								}
							}
						}
						else if (!strncmp(p->f_in->s->buf + pos,
									"free",
									p->f_in->s->read_pos - pos))
						{
							if (parse_get_char(p->f_in->s) == ';' ||
									p->f_in->s->read_pos + 1 >= p->f_in->s->write_pos)
							{
								is_var_type = 1;
							}
							else
							{
								is_free = 1;
								if (parse_lws(p->f_in->s))
								{
								}
								pos = p->f_in->s->read_pos;
								if (parse_identifier(p->f_in->s))
								{
									is_var_type = 1;
								}
							}
						}
						else
						{
							is_var_type = 1;
						}
					}
					if (is_var_type)
					{
						// var type
						p->s_var_type = char_string_read_char_size(p->s_var_type,
								p->f_in->s->buf + pos,
								p->f_in->s->read_pos - pos);
						is_var_type = 0;
						if (parse_lws(p->f_in->s))
						{
						}
						pos = p->f_in->s->read_pos;
						pos_var = pos;
						pos_var_type = pos_var;
						while (parse_identifier(p->f_in->s))
						{
							pos_var_type = pos_var;
							pos_var = p->f_in->s->read_pos;
							if (is_pointer)
							{
								break;
							}
							if (parse_lws(p->f_in->s))
							{
							}
							if (parse_asterisk(p->f_in->s))
							{
								is_pointer = 1;
							}
							if (parse_lws(p->f_in->s))
							{
							}
						}
						if (pos < pos_var_type)
						{
							p->s_var_type = char_string_add_char(p->s_var_type,
									" ",
									1,
									0);
							p->s_var_type = char_string_add_char(p->s_var_type,
									p->f_in->s->buf + pos,
									pos_var_type - pos,
									0);
							p->f_in->s->read_pos = pos_var_type;
							if (parse_lws(p->f_in->s))
							{
							}
						}
						else
						{
							p->f_in->s->read_pos = pos;
						}
						if (parse_asterisk(p->f_in->s))
						{
							is_pointer = 1;
						}
						if (parse_lws(p->f_in->s))
						{
						}
						pos = p->f_in->s->read_pos;
						if (parse_identifier(p->f_in->s))
						{
							pos_var = p->f_in->s->read_pos;
							// var
							p->s_var = char_string_read_char_size(p->s_var,
									p->f_in->s->buf + pos,
									p->f_in->s->read_pos - pos);
							p->s_struct = char_string_add_char(p->s_struct,
									"VAR",
									0,
									0);
							if (is_pointer)
							{
								p->s_struct = char_string_add_char(p->s_struct,
										"_POINTER",
										0,
										0);
								is_pointer = 0;
								if (is_create)
								{
									p->s_struct = char_string_add_char(p->s_struct,
											"_CREATE",
											0,
											0);
									is_create = 0;
								}
								else if (is_init)
								{
									p->s_struct = char_string_add_char(p->s_struct,
											"_INIT",
											0,
											0);
									is_init = 0;
								}
								else if (is_free)
								{
									p->s_struct = char_string_add_char(p->s_struct,
											"_FREE",
											0,
											0);
									is_free = 0;
								}
							}
							p->s_struct = char_string_add_char(p->s_struct,
									"(",
									0,
									0);
							p->s_struct = char_string_add(p->s_struct,
									p->s_var_type,
									0);
							p->s_struct = char_string_add_char(p->s_struct,
									",",
									0,
									0);
							p->s_struct = char_string_add(p->s_struct,
									p->s_var,
									0);
							p->s_struct = char_string_add_char(p->s_struct,
									")\n",
									0,
									0);
							is_set++;
						}
						else if (!is_create &&
								!is_init &&
								!is_free &&
								!is_pointer)
						{
							// flag
							p->s_struct_flags = char_string_add_char(p->s_struct_flags,
									"FLAG(",
									0,
									0);
							p->s_struct_flags = char_string_add(p->s_struct_flags,
									p->s_var_type,
									0);
							p->s_struct_flags = char_string_add_char(p->s_struct_flags,
									")\n",
									0,
									0);
							is_set++;
						}
						else
						{
							is_create = 0;
							is_init = 0;
							is_free = 0;
							is_pointer = 0;
						}
					}
				}
				else
				{
					break;
				}
			}
			if (is_set > 0)
			{
				if (FUNC(open_file)(p,
							SECTION_STRUCT_FILE_NAME,
							"w"))
				{
					p->f_section->s = char_string_copy(p->f_section->s,
							p->s_struct);
					if (char_string_check(p->s_struct_flags))
					{
						p->f_section->s = char_string_add_char(p->f_section->s,
								"FLAGS(\n",
								0,
								0);
						p->f_section->s = char_string_add(p->f_section->s,
								p->s_struct_flags,
								0);
						p->f_section->s = char_string_add_char(p->f_section->s,
								")\n",
								0,
								0);
					}
					is_set = file_write(p->f_section);
					if (is_set > 0)
					{
						p->f_in->s = char_string_read_char(p->f_in->s,
								"#define MODULE_STRUCT ");
						p->f_in->s = char_string_add(p->f_in->s,
								p->s_module,
								0);
						p->f_in->s = char_string_add_char(p->f_in->s,
								"_" SECTION_STRUCT_FILE_NAME "\n",
								0,
								0);
						is_set = FUNC(write_out)(p);
					}
				}
			}
		}
	}

	return is_set;
}

#undef SECTION_STRUCT_FILE_NAME

#endif	/* SECTION_STRUCT_H */

