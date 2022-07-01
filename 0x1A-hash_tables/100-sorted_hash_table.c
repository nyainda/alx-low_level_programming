#include "hash_tables.h"

/**
 * hash_table_create - creates a hash table
 * @size: size to create hash table with
 * Return: Returns the newly created hash table
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *new_table = malloc(sizeof(shash_table_t));
	unsigned long int index;

	if (new_table == NULL)
	{
		free(new_table);
		return (NULL);
	}

	new_table->size = size;
	new_table->array = malloc(sizeof(shash_node_t *) * size);

	if (new_table->array == NULL)
	{
		free(new_table->array), free(new_table);
		return (NULL);
	}

	for (index = 0; index < size; index++)
		new_table->array[index] = NULL;

	return (new_table);
}

/**
 * shash_table_set - table
 * @ht: ht
 * @key: key
 * @value: value
 * Return: Int
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	shash_node_t *new, *oldhead, *search;

	if (!ht || !key || strcmp(key, "") == 0)
		return (0);

	index = key_index((unsigned char *)key, ht->size);
	for (search = ht->array[index]; search; search = search->next)
		if (strcmp(search->key, key) == 0)
		{
			free(search->value);
			search->value = strdup(value);
			return (1);
		}

	new = malloc(sizeof(shash_node_t));
	if (new == NULL)
		return (0);
	new->value = strdup(value);
	new->key = strdup(key);
	seeker(ht, ht->array[index]); /* Handles sPrev and sNext */

	/* CASE 1: If a singly linked list isn't there */
	if (ht->array[index] == NULL)
	{
		ht->array[index] = new;
		new->next = NULL;
	}

	/* CASE 2: If a singly linked list is there, make one */
	else
	{
		oldhead = ht->array[index];	/* Keep a copy of our current head */
		new->next = oldhead;		/* Our new node should now point to old head */
		ht->array[index] = new;		/* Make our new node the head */
	}
	return (1);
}

/**
 * seeker - seeks the meaning of laef
 * @ht: hash table
 * @node: node
 * Return: Always void
 */
int *seeker(shash_table_t *ht, shash_node_t *node)
{
	unsigned long int index;
	int i;
	shash_node_t *search;
	char *alpha[] = {
		"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n",
			"o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", NULL};

	for (i = 0; alpha[i] != NULL; i++)
	{
		index = key_index((unsigned char *)alpha, ht->size);
		for (search = ht->array[index]; search; search = search->next)
		{
			if (alpha[i][0] < search->key[0])
				node->sprev = search, node->snext = NULL, ht->shead = node->sprev;
			else
				node->snext = search, node->sprev = NULL, ht->stail = node->snext;
		}
	}
	return (0);
}

/**
 * shash_table_print - prints out all
 * of the elements in the hash table
 * @ht: hash table
 * Return: Always Void
 */
void shash_table_print(const shash_table_t *ht)
{
	unsigned long int index;
	int flag = 0;
	shash_node_t *temp;

	if (ht)
	{
		printf("{");
		for (index = 0; index < ht->size; index++)
		{
			if (ht->array[index] == NULL)
				continue;

			if (ht->array[index])
				for (temp = ht->array[index]; temp; temp = temp->next)
				{
					if (flag == 1)
						printf(", ");
					printf("'%s': '%s'", temp->key, temp->value), flag = 1;
				}
		}
		printf("}\n");
	}
}

/**
 * shash_table_print_rev - rev
 * @ht: ht
 * Return: Void
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	unsigned long int index;
	int flag = 0;
	shash_node_t *temp;

	if (ht)
	{
		printf("{");
		for (index = ht->size - 1; index > 0; index--)
		{
			if (ht->array[index])
				for (temp = ht->array[index]; temp; temp = temp->next)
				{
					if (flag == 1)
						printf(", ");
					printf("'%s': '%s'", temp->key, temp->value), flag = 1;
				}
		}
		printf("}\n");
	}
}

/**
 * hash_table_delete - gets rid of the
 * hashtable
 * @ht: hash table
 * Return: Always Void
 */
void shash_table_delete(shash_table_t *ht)
{
	unsigned long int index;

	for (index = 0; index < ht->size; index++)
		if (ht->array[index] != NULL)
			free_shtack(ht->array[index]);
	free(ht->array); /* 233 | 8245 */
	free(ht); /* Frees the hash table */
}

/**
 * free_stack - frees the stack
 * @head: doubly linked list
 * Return: Always Void
 */
void free_shtack(shash_node_t *head)
{
	shash_node_t *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->value);
		free(temp->key);
		free(temp);
	}
}
#include "hash_tables.h"

/**
 * hash_table_get - retrives the value
 * using the given key.
 * @ht: hash table
 * @key: key
 * Return: NULL on Fail | Value on Pass
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int index;
	char *value = NULL;
	shash_node_t *search;

	if (!key || !ht || strcmp(key, "") == 0)
		return (value);

	index = key_index((unsigned char *)key, ht->size);

		if (ht->array[index])
		{
			for (search = ht->array[index]; search; search = search->next)
			{
				if (strcmp(search->key, key) == 0)
				{
					value = search->value;
					break;
				}
			}
		}
	return (value);
}
