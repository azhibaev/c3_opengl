p->section_index = -1;
p->is_module = 0;
p->s_path_out = char_string_read_char(p->s_path_out,
		path_out);
file_init(p->f_in,
		f_in,
		"r");
