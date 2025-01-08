#ifndef SECTION_FREE_H
#define SECTION_FREE_H

#define SECTION_FREE_FILE_NAME "free.h"
#define SECTION_FREE_VAR_FILE_NAME "free_var.h"

FUNCTION_INLINE int FUNC(section_free)(T *p)
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
			p->s_free = char_string_reset_init(p->s_free);
			p->s_free_var = char_string_reset_init(p->s_free_var);
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
						p->s_free_var = char_string_add_char(p->s_free_var,
								"PARAMETER",
								0,
								0);
						if (is_pointer)
						{
							p->s_free_var = char_string_add_char(p->s_free_var,
									"_POINTER",
									0,
									0);
							is_pointer = 0;
						}
						p->s_free_var = char_string_add_char(p->s_free_var,
								"(",
								0,
								0);
						p->s_free_var = char_string_add(p->s_free_var,
								p->s_var_type,
								0);
						p->s_free_var = char_string_add_char(p->s_free_var,
								",",
								0,
								0);
						p->s_free_var = char_string_add(p->s_free_var,
								p->s_var,
								0);
						p->s_free_var = char_string_add_char(p->s_free_var,
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
											p->s_free_var = char_string_add_char(p->s_free_var,
													"VAR",
													0,
													0);
											if (is_pointer)
											{
												p->s_free_var = char_string_add_char(p->s_free_var,
														"_POINTER",
														0,
														0);
												is_pointer = 0;
											}
											p->s_free_var = char_string_add_char(p->s_free_var,
													"(",
													0,
													0);
											p->s_free_var = char_string_add(p->s_free_var,
													p->s_var_type,
													0);
											p->s_free_var = char_string_add_char(p->s_free_var,
													",",
													0,
													0);
											p->s_free_var = char_string_add(p->s_free_var,
													p->s_var,
													0);
											p->s_free_var = char_string_add_char(p->s_free_var,
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
						p->s_free = char_string_add(p->s_free,
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
				if (char_string_check(p->s_free))
				{
					if (FUNC(open_file)(p,
								SECTION_FREE_FILE_NAME,
								"w"))
					{
						p->f_section->s = char_string_copy(p->f_section->s,
								p->s_free);
						is_set = file_write(p->f_section);
						if (is_set > 0)
						{
							p->f_in->s = char_string_read_char(p->f_in->s,
									"#define MODULE_FREE ");
							p->f_in->s = char_string_add(p->f_in->s,
									p->s_module,
									0);
							p->f_in->s = char_string_add_char(p->f_in->s,
									"_" SECTION_FREE_FILE_NAME "\n",
									0,
									0);
							is_set = FUNC(write_out)(p);
						}
					}
				}
				if (char_string_check(p->s_free_var))
				{
					if (FUNC(open_file)(p,
								SECTION_FREE_VAR_FILE_NAME,
								"w"))
					{
						p->f_section->s = char_string_copy(p->f_section->s,
								p->s_free_var);
						is_set = file_write(p->f_section);
						if (is_set > 0)
						{
							p->f_in->s = char_string_read_char(p->f_in->s,
									"#define MODULE_FREE_VAR ");
							p->f_in->s = char_string_add(p->f_in->s,
									p->s_module,
									0);
							p->f_in->s = char_string_add_char(p->f_in->s,
									"_" SECTION_FREE_VAR_FILE_NAME "\n",
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

#undef SECTION_FREE_FILE_NAME
#undef SECTION_FREE_VAR_FILE_NAME

#endif	/* SECTION_FREE_H */

