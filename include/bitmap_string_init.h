p->type = draw_item_type_bitmap_string;
p->font = GLUT_BITMAP_TIMES_ROMAN_24;
if (s)
{
	size = strlen(s);
	if (p->buf &&
			p->size > size)
	{
		memcpy(p->buf,
				s,
				size);
		p->buf[size] = 0;
	}
	else
	{
		if (p->buf)
		{
			free(p->buf);
			p->size = 0;
		}
		p->buf = malloc((size + 2) * sizeof(char));
		if (p->buf)
		{
			p->size = size + 2;
			memcpy(p->buf,
					s,
					size);
			p->buf[size] = 0;
		}
	}
}
