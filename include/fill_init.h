p->ab = ab;
p->base = base;
if (draw)
{
	p->draw = mul_draw_create_init(1,
			draw);
}
else
{
	p->draw = NULL;
}
p->is_print = 1;
