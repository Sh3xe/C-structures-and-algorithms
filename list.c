#include "list.h"
#include <stdlib.h>
#include <assert.h>

static bool lst_reallocate( lst_t *list, uint32_t new_size )
{
	// test wether it is really necessary to reallocate the list
	if( list->allocated_size >= new_size )
		return true;

	// allocation of the new list
	int *new_list_items = (int*)malloc( sizeof(int) * new_size );
	if(new_list_items == NULL)
		return false;

	// copying the old elements
	for(uint32_t i = 0; i < lst_size(list); ++i)
		new_list_items[i] = lst_nth(list, i);

	list->allocated_size = new_size;
	list->begin_id = 0;

	free(list->elements);
	list->elements = new_list_items;

	return true;
}

bool lst_create( lst_t *list, uint32_t initial_size )
{
	list->allocated_size = initial_size;
	list->begin_id = 0;
	list->current_size = 0;
	list->elements = (int*)malloc( sizeof(int) * initial_size );
	return list->elements != NULL;
}

void lst_destroy( lst_t *list )
{
	free(list->elements);
}

int lst_nth( lst_t *list, uint32_t index )
{
	return list->elements[(list->begin_id + index) % list->allocated_size];
}

bool lst_push_back( lst_t *list, int element )
{
	if( list->allocated_size < list->current_size + 1)
	{
		// use the "multiply by two" strategy that ensures that adding N elements to a list is in O(N)
		uint32_t new_size = (list->allocated_size == 0) ? 4: list->allocated_size * 2;
		// handle the specific case where the size is superior to the UINT32_MAX
		if( new_size < list->allocated_size)
			return false;
		// allocates new memory for the elements
		bool res = lst_reallocate(list, list->current_size * 2);
		
		if( !res )
			return false;
	}

	// add the element...
	list->elements[(list->begin_id+list->current_size) % list->allocated_size] = element;
	++list->current_size;
	return true;
}

int lst_pop_back( lst_t *list )
{
	assert(list->current_size > 0);

	int item = list->elements[(list->begin_id + (list->current_size-1)) % list->allocated_size];
	--list->current_size;
	
	return item;
}

bool lst_push_front( lst_t *list, int element )
{
	if( list->allocated_size < list->current_size + 1)
	{
		// use the "multiply by two" strategy that ensures that adding N elements to a list is in O(N)
		uint32_t new_size = (list->allocated_size == 0) ? 4: list->allocated_size * 2;
		// handle the specific case where the size is superior to the UINT32_MAX
		if( new_size < list->allocated_size)
			return false;
		// allocates new memory for the elements
		bool res = lst_reallocate(list, list->current_size * 2);
		
		if( !res )
			return false;
	}

	// add the element...
	int new_begin_id = (list->begin_id - 1 + list->allocated_size) % list->allocated_size;
	list->elements[new_begin_id] = element;
	list->begin_id = new_begin_id;
	++list->current_size;
	return true;
}

int lst_pop_front( lst_t *list )
{
	assert( list->current_size > 0 );

	--list->current_size;
	int front = list->elements[list->begin_id];
	list->begin_id = (list->begin_id+1) % list->allocated_size;
	return front;
}

uint32_t lst_size( lst_t *list )
{
	return list->current_size;
}

int lst_copy( lst_t *in, lst_t *out )
{
	
}