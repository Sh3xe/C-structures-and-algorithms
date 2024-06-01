#include "union_find.h"
#include <assert.h>
#include <stdlib.h> 

uf_t *uf_create( int size )
{
	uf_t *uf = (uf_t*)malloc( sizeof(uf_t) );
	uf->size = size;
	uf->data = (int*)malloc( size*sizeof(int) );
	uf->heights = (int*)malloc( size*sizeof(int) );

	for( int i = 0; i < size; ++i )
	{
		uf->heights[i] = 1;
		uf->data[i] = -1;
	}

	return uf;
}

void uf_free( uf_t *uf )
{
	free( uf );
}

int uf_find( uf_t *uf, int x )
{
	assert( x < uf->size );
	int index = x;
	while( uf->data[index] != -1 )
		index = uf->data[index];

	if( uf->data[x] != -1 )
		uf->data[x] = index;
	
	return index;
}

void uf_union( uf_t *uf, int x, int y )
{
	assert( x < uf->size && y < uf->size );
	int px = uf_find( uf, x );
	int py = uf_find( uf, y );

	if( uf->heights[px] > uf->heights[py] )
		uf->data[px] = py;
	else if( uf->heights[px] < uf->heights[py] )
		uf->data[py] = px;
	else
	{
		uf->data[px] = py;
		++uf->heights[px];
	}
}
