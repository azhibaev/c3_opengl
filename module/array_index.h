#ifndef ARRAY_INDEX_H
#define ARRAY_INDEX_H

#define ARRAY_INDEX(s) {#s, sizeof(#s) - 1, s ## _index}
#define ARRAY_INDEX_I(s,i) {s, sizeof(s) - 1, i ## _index}
#define ARRAY_INDEX_E(s) s ## _index
#define ARRAY_INDEX_I_E(s,i) i ## _index
#define ARRAY_INDEX_SIZE(a) (sizeof(a) / sizeof(a[0]))

typedef struct array_index
{
	const char *s;
	size_t size;
	size_t index;
}
array_index;

#endif	/* ARRAY_INDEX_H */

