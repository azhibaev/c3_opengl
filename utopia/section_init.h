#ifndef SECTION_INIT_H
#define SECTION_INIT_H

#define SECTION_INIT_FILE_NAME "init.h"
#define SECTION_INIT_VAR_FILE_NAME "init_var.h"

FUNCTION_INLINE int FUNC(section_init)(T *p)
{
	int is_set = 0;
	size_t pos = 0;
	int is_var = 1;
	int is_pointer = 0;
	size_t pos_var = 0;
	size_t pos_var_type = 0;

	if (p)
	{
		if (p->f_in)
		{
			p->s_init = char_string_reset_init(p->s_init);
			p->s_init_var = char_string_reset_init(p->s_init_var);
			if (parse_lws(p->f_in->s))
			{
			}
			if (parse_ch(p->f_in->s,
						'('))
			{
				pos = p->f_in->s->read_pos;
				while (parse_identifier(p->f_in->s))
				{
					p->s_var_type = char_string_read_char_size(p->s_var_type,
							p->f_in->s->buf + pos,
							p->f_in->s->read_pos - pos);
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
						p->s_var = char_string_read_char_size(p->s_var,
								p->f_in->s->buf + pos,
								p->f_in->s->read_pos - pos);
						p->s_init_var = char_string_add_char(p->s_init_var,
								"PARAMETER",
								0,
								0);
						if (is_pointer)
						{
							p->s_init_var = char_string_add_char(p->s_init_var,
									"_POINTER",
									0,
									0);
							is_pointer = 0;
						}
						p->s_init_var = char_string_add_char(p->s_init_var,
								"(",
								0,
								0);
						p->s_init_var = char_string_add(p->s_init_var,
								p->s_var_type,
								0);
						p->s_init_var = char_string_add_char(p->s_init_var,
								",",
								0,
								0);
						p->s_init_var = char_string_add(p->s_init_var,
								p->s_var,
								0);
						p->s_init_var = char_string_add_char(p->s_init_var,
								")\n",
								0,
								0);
					}
					if (parse_lws(p->f_in->s))
					{
					}
					if (parse_ch(p->f_in->s,
								')'))
					{
						break;
					}
					if (!parse_ch(p->f_in->s,
								','))
					{
						break;
					}
					if (parse_lws(p->f_in->s))
					{
					}
					pos = p->f_in->s->read_pos;
				}
			}
			while (file_read_line(p->f_in))
			{
				if (char_string_check(p->f_in->s))
				{
					if (is_var)
					{
						is_var = 0;
						pos = p->f_in->s->read_pos;
						if (parse_identifier(p->f_in->s))
						{
							// var type
							p->s_var_type = char_string_read_char_size(p->s_var_type,
									p->f_in->s->buf + pos,
									p->f_in->s->read_pos - pos);
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
							pos = p->f_in->s->read_pos;
							if (parse_identifier(p->f_in->s))
							{
								// var
								if (parse_lws(p->f_in->s))
								{
								}
								if (parse_ch(p->f_in->s,
											'='))
								{
									if (char_string_check(p->f_in->s))
									{
										if (p->f_in->s->buf[p->f_in->s->write_pos - 1] == ';')
										{
											p->f_in->s->read_pos = p->f_in->s->write_pos - 1;
											p->s_var = char_string_read_char_size(p->s_var,
													p->f_in->s->buf + pos,
													p->f_in->s->read_pos - pos);
											is_var++;
											p->s_init_var = char_string_add_char(p->s_init_var,
													"VAR",
													0,
													0);
											if (is_pointer)
											{
												p->s_init_var = char_string_add_char(p->s_init_var,
														"_POINTER",
														0,
														0);
												is_pointer = 0;
											}
											p->s_init_var = char_string_add_char(p->s_init_var,
													"(",
													0,
													0);
											p->s_init_var = char_string_add(p->s_init_var,
													p->s_var_type,
													0);
											p->s_init_var = char_string_add_char(p->s_init_var,
													",",
													0,
													0);
											p->s_init_var = char_string_add(p->s_init_var,
													p->s_var,
													0);
											p->s_init_var = char_string_add_char(p->s_init_var,
													")\n",
													0,
													0);
											is_set++;
										}
									}
								}
							}
						}
					}
					if (!is_var)	
					{
						p->f_in->s->read_pos = 0;
						if (p->f_in->s->buf[p->f_in->s->write_pos] == '\n')
						{
							p->f_in->s->write_pos++;
						}
						p->s_init = char_string_add(p->s_init,
								p->f_in->s,
								0);
						is_set++;
					}
				}
				else
				{
					break;
				}
			}
			if (is_set > 0)
			{
				if (char_string_check(p->s_init))
				{
					if (FUNC(open_file)(p,
								SECTION_INIT_FILE_NAME,
								"w"))
					{
						p->f_section->s = char_string_copy(p->f_section->s,
								p->s_init);
						is_set = file_write(p->f_section);
						if (is_set > 0)
						{
							p->f_in->s = char_string_read_char(p->f_in->s,
									"#define MODULE_INIT ");
							p->f_in->s = char_string_add(p->f_in->s,
									p->s_module,
									0);
							p->f_in->s = char_string_add_char(p->f_in->s,
									"_" SECTION_INIT_FILE_NAME "\n",
									0,
									0);
							is_set = FUNC(write_out)(p);
						}
					}
				}
				if (char_string_check(p->s_init_var))
				{
					if (FUNC(open_file)(p,
								SECTION_INIT_VAR_FILE_NAME,
								"w"))
					{
						p->f_section->s = char_string_copy(p->f_section->s,
								p->s_init_var);
						is_set = file_write(p->f_section);
						if (is_set > 0)
						{
							p->f_in->s = char_string_read_char(p->f_in->s,
									"#define MODULE_INIT_VAR ");
							p->f_in->s = char_string_add(p->f_in->s,
									p->s_module,
									0);
							p->f_in->s = char_string_add_char(p->f_in->s,
									"_" SECTION_INIT_VAR_FILE_NAME "\n",
									0,
									0);
							is_set = FUNC(write_out)(p);
						}
					}
				}
			}
		}
	}

	return is_set;
}

#undef SECTION_INIT_FILE_NAME
#undef SECTION_INIT_VAR_FILE_NAME

#endif	/* SECTION_INIT_H */

