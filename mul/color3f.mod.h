#ifndef COLOR3F_H
#define COLOR3F_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_def.h"
#include "char_string.h"

#module color3f

#struct
size_t type;
double r;
double g;
double b;

#init (double r, double g, double b)
p->type = draw_item_type_color3f;
p->r = r;
p->g = g;
p->b = b;

#include "module.h"

FUNCTION_INLINE int FUNC(hex)(T *p,
		unsigned int i)
{
	int is_set = 0;

	if (p)
	{
		p->r = (double) ((i >> 16) & 0xff) / 0xff;
		p->g = (double) ((i >> 8) & 0xff) / 0xff;
		p->b = (double) (i & 0xff) / 0xff;
		is_set = 1;
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(hsv)(T *p,
		int hue,
		double saturation,
		double value)
{
	int is_set = 0;
	int hi = 0;
	int f = 0;
	int p1 = 0;
	int q = 0;
	int t = 0;
	struct rgb
	{
		int r;
		int g;
		int b;
	} rgb;

	if (p)
	{
		hi = (hue / 60) % 6;
		f = hue / 60 - hi;
		p1 = value * (1 - saturation);
		q = value * (1 - f * saturation);
		t = value * (1 - (1 - f) * saturation);

		switch (hi)
		{
			case 0:
				rgb = (struct rgb){value, t, p1};
				break;
			case 1:
				rgb = (struct rgb){q, value, p1};
				break;
			case 2:
				rgb = (struct rgb){p1, value, t};
				break;
			case 3:
				rgb = (struct rgb){p1, q, value};
				break;
			case 4:
				rgb = (struct rgb){t, p1, value};
				break;
			case 5:
				rgb = (struct rgb){value, p1, q};
				break;
			default:
				break;
		}

		p->r = rgb.r;
		p->g = rgb.g;
		p->b = rgb.b;
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(inc)(T *p,
		size_t i)
{
	int is_set = 0;
	unsigned int c = 0;
	unsigned int w = 0;
	unsigned int a = 0;

	if (p)
	{
		w = 1 << (i - 1);
		a = (1 << i) - 1;
		c = ((int) (p->r * w)) << (i * 2);
		c += ((int) (p->g * w)) << i;
		c += (int) (p->b * w);
		c++;
		p->r = (double) ((c >> (i * 2)) & a) / a;
		p->g = (double) ((c >> i) & a) / a;
		p->b = (double) (c & a) / a;
	}

	return is_set;
}

FUNCTION_INLINE int FUNC(print)(T *p)
{
	int is_set = 0;

	if (p)
	{
		printf("%2x%2x%2x",
				(int)(p->r * 256),
				(int)(p->g * 256),
				(int)(p->b * 256));
		is_set = 1;
	}

	return is_set;
}

#include "module_undef.h"

#endif	/* COLOR3F_H */
