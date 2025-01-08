if (p->is_init)
{
	if (p->is_alloc &&
			p->buf)
	{
		free(p->buf);
	}
	is_free = 1;
}
