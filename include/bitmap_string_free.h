if (p->buf)
{
	free(p->buf);
	p->buf = NULL;
	p->size = 0;
}
