p->file_name = char_string_read_char(p->file_name,
		file_name);
p->options = char_string_read_char(p->options,
		options);
if (!p->s)
{
	p->s = char_string_create_init(1,
			1 KB);
}
if (p->file_name &&
		p->options)
{
	if (p->f)
	{
		fclose(p->f);
	}
	p->f = fopen(p->file_name->buf,
			p->options->buf);
}
