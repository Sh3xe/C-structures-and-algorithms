#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct al_node_t {
	char *key;
	int value;
	struct al_node_t *next;
} al_node_t;

typedef struct al_t {
	al_node_t *begin_node;
} al_t;

/**
 * @brief Creates an empty associative list
 * 
 * @param list 
*/
void al_create(al_t *list);

/**
 * @brief free the memory of list
 * 
 * @param list 
 */
void al_destroy(al_t *list);

/**
 * @brief add (key,value) to list
 * 
 * @param list 
 * @param key 
 * @param value 
 * @return false in case of memory allocation error
 */
bool al_push(al_t *list, const char *key, int value);

/**
 * @brief remove the association (key, *) from the list
 * 
 * @param list 
 * @param key 
 */
void al_remove(al_t *list, const char *key);

/**
 * @brief get the value associated with key in list
 * 
 * @param list 
 * @param key 
 * @param out_value return value
 * @return true if the element was found (the result is in *value)
 * @return false if the element was not found
 */
bool al_get(al_t *list, const char *key, int *out_value);

typedef struct ht_t {
	uint32_t size;
	al_t *data;
} ht_t;

/**
 * @brief Fills the hash table ht.
 * 
 * @param list 
 * @param default_size the number of associative lists allocated, should be ~ the amount of elements you will put in
 * @return true for success
 * @return false in case of allocation errors
 */
bool ht_create(ht_t *ht, uint32_t default_size);

/**
 * @brief free the memory of ht
 * 
 * @param ht 
 */
void ht_destroy(ht_t *ht);

/**
 * @brief add the (key,value) pair to the dictionnary
 * 
 * @param ht hash table where the pair will be added
 * @param key 
 * @param value 
 * @return true success
 * @return false in case ofmemory allocation error
 */
bool ht_push(ht_t *ht, const char *key, int value);

/**
 * @brief removes the (key,value) pair to the dictionnary
 * 
 * @param ht hash table where the pair will be removed
 * @param key 
 */
void ht_remove(ht_t *ht, const char *key);

/**
 * @brief get the value associated with key in ht
 * 
 * @param list 
 * @param key 
 * @param out_value return value
 * @return true if the element was found (the result is in *value)
 * @return false if the element was not found
 */
bool ht_get(ht_t *ht, const char *key, int *out_value);