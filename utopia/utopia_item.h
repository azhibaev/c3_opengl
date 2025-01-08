#ifndef UTOPIA_ITEM_H
#define UTOPIA_ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// module
utopia_list

// struct
void *next;
void *prev;
void *p;

void* next(T *p)
{
	if (p)
	{
		if (p->next)
		{
			p->p = p->next;
			return p->p;
		}
	}

	return NULL;
}

int print(T *p)
{
	int is_set = 0;

	if (p)
	{
		printf("%lld * %lld = %lld\n",
				p->m1,
				p->m2,
				p->p);
		is_set = 1;
	}

	return is_set;
}


#endif	/* UTOPIA_ITEM_H */
