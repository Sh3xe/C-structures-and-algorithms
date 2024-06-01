#ifndef UNION_FIND_H
#define UNION_FIND_H

typedef struct uf_t {
	int size;
	int *data;
	int *heights;
} uf_t;

uf_t *uf_create( int size );
void uf_free( uf_t *uf );

void uf_union( uf_t *uf, int x, int y );
int uf_find( uf_t *uf, int x );

#endif