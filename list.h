#pragma one

#include <stdint.h>
#include <stdbool.h>

typedef struct lst_t {
	uint32_t allocated_size;
	uint32_t current_size;
	uint32_t begin_id;
	int *elements;
} lst_t;

/**
 * @brief initialize the memory in list.
 * 
 * @param list a pointer to the memory to init
 * @param initial_size the size allocated by default.
 * @return true if there is no errors
 * @return false in case of memory errors
 */
bool lst_create( lst_t *list, uint32_t initial_size );

/**
 * @brief free the memory of the list. you can reuse lst_init on list after calling this function
 * 
 * @param list, the list to free
 */
void lst_destroy( lst_t *list );

/**
 * @brief returns the elements at index index in list. Will assert false if the list is empty, you should alwase call lst_empty to check if the list is empty
 * 
 * @param list the list...
 * @param index the index...
 * @return the element at index index.
 */
int lst_nth( lst_t *list, uint32_t index );

/**
 * @brief add an item at the end of the list
 * 
 * @param list the list...
 * @param element the element to push...
 * @return true in case of success
 * @return false in case of errors (allocation errors)
 */
bool lst_push_back( lst_t *list, int element );

int lst_pop_back( lst_t *list );
bool lst_push_front( lst_t *list, int element );
int lst_pop_front( lst_t *list );
int lst_copy( lst_t *in, lst_t *out );
uint32_t lst_size( lst_t *list );