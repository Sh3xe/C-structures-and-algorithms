#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

static uint32_t hash_string(const char *str)
{
	uint32_t value = 0;
	uint32_t multiplier = 1;

	for(size_t i = 0; str[i] != '\0'; ++i)
	{
		value += multiplier * (uint32_t)str[i];
		multiplier *= 256;
	}

	return value;
}

void al_create(al_t *list)
{
	list->begin_node = NULL;
}

void al_destroy(al_t *list)
{
	// iterate over the associative list's nodes
	for(al_node_t *current_node = list->begin_node; current_node != NULL;)
	{
		al_node_t *node = current_node;
		current_node = node->next;

		// free the current node
		free(node->key);
	}
}

bool al_push(al_t *list, const char *key, int value)
{
	al_node_t *current_node = list->begin_node;
	al_node_t *last_node = NULL;

	while( current_node != NULL )
	{
		if(strcmp(current_node->key, key) == 0)
		{
			// key does already exist, just change the value associated with it
			current_node->value = value;
			return true;
		}

		last_node =  current_node;
		current_node = current_node->next;
	}

	// allocates the node
	al_node_t *new_node = malloc(sizeof(al_node_t));
	if(new_node == NULL) return false;
	new_node->value = value;
	new_node->key = malloc( (strlen(key)+1)*sizeof(char) );
	if(new_node->key == NULL) return false;
	strcpy(new_node->key, key);
	new_node->next = NULL;

	// we pushed the first item of the list
	if(last_node == NULL)
	{
		list->begin_node = new_node;
	}
	// the list is not empty, add the node at the end
	else
	{
		last_node->next = new_node;
	}

	return true;
}

void al_remove(al_t *list, const char *key)
{
	al_node_t *current_node = list->begin_node;
	al_node_t *last_node = NULL;

	while( current_node != NULL )
	{
		// we found the key
		if(strcmp(current_node->key, key) == 0)
		{
			if(last_node == NULL)
				list->begin_node = current_node->next;
			else
				last_node->next = current_node->next;

			free(current_node->key);
			free(current_node);
			return;
		}

		last_node =  current_node;
		current_node = current_node->next;
	}
}

bool al_get(al_t *list, const char *key, int *value)
{
	for(al_node_t *it = list->begin_node; it != NULL; it = it->next)
	{
		if(strcmp(it->key, key) == 0)
		{
			*value = it->value;
			return true;
		}
	}

	return false;
}

bool ht_create(ht_t *ht, uint32_t default_size)
{
	ht->size = default_size;
	ht->data = malloc(ht->size * sizeof(al_t));

	if(ht->data == NULL) return false;

	for(size_t i = 0; i < ht->size; ++i)
	{
		al_create(&ht->data[i]);
	}

	return true;
}

void ht_destroy(ht_t *ht)
{
	for(size_t i = 0; i < ht->size; ++i)
	{
		al_destroy(&ht->data[i]);
	}

	free(ht->data);
}

bool ht_push(ht_t *ht, const char *key, int value)
{
	size_t index = hash_string(key) % ht->size;
	return al_push(&ht->data[index], key, value);
}

void ht_remove(ht_t *ht, const char *key)
{
	size_t index = hash_string(key) % ht->size;
	al_remove(&ht->data[index], key);
}

bool ht_get(ht_t *ht, const char *key, int *out_value)
{
	size_t index = hash_string(key) % ht->size;
	return al_get(&ht->data[index], key, out_value);
}