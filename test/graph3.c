#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mul.h"
#include "list.h"
#include "fill.h"
#include "graph.h"
#include "mul_draw.h"
#include "prime.h"
#include "find_line.h"

int main(int argc, const char *argv[])
{
	mul *m = NULL;
	list *list = NULL;
	fill *fill = NULL;
	size_t i = 0;
	list_item *item = NULL;
	graph *g = NULL;
	mul_draw *draw = NULL;
	prime *prime = NULL;
	find_line *fl = NULL;
	size_t n = 2;
	size_t width = 1000;
	size_t height = 1000;
	size_t scale = 10;
	size_t base = 10;
	long long a = 1512;
	long long b = 2162;

	g = graph_create_init(1,
			width,
			height,
			scale,
			"Test");

	prime = prime_create_init(1,
			100,
			100000);

	a = prime_get_i(prime,
			a);
	b = prime_get_i(prime,
			b);

	m = mul_create_init(1,
			a,
			b);
	mul_print(m);
	printf("\n");

	list = list_create(1);
	fill = fill_create_init(1,
			m->p,
			base,
			g->draw);

	i = 1;
	fill_row(fill,
			list,
			item,
			1);
//	list_remove_if(list,
//			fill_mul_eq);
	i++;
	fill_n(fill,
			list,
			item,
			i,
			n);

	fl = find_line_create_init(1,
			2,
			2);

	find_line_list(fl,
			list);

	find_line_lines(fl);
	find_line_points(fl);

	draw = mul_draw_create_init(1,
			g->draw);
	color3f_hex(draw->text_color,
			0x00ff00);
	color3f_hex(draw->line_color,
			0x808080);
	mul_draw_point2f(draw,
			fl->points,
			width,
			n,
			base);

	draw = mul_draw_create_init(1,
			g->draw);
	color3f_hex(draw->text_color,
			0xffff00);
	color3f_hex(draw->line_color,
			0xffff00);
	mul_draw_point(draw,
			m,
			width,
			n,
			base);

	mul_init(m,
			b,
			a);

	draw = mul_draw_create_init(1,
			g->draw);
	color3f_hex(draw->text_color,
			0x00ffff);
	color3f_hex(draw->line_color,
			0x00ffff);
	mul_draw_point(draw,
			m,
			width,
			n,
			base);

	graph_start(g,
			argc,
			(char**)argv);

	return 0;
}

