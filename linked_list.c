#include "shell.h"

/**
 * add_node - Add an element to the start of the linked list.
 * @head: Address of the pointer to the head element.
 * @str: The string field of the new element.
 * @num: The element index used for history.
 *
 * Return: The new head of the list.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	/* Implementation */
}

/**
 * add_node_end - Add a node to the end of the linked list.
 * @head: Address of the pointer to the head node.
 * @str: The string field of the new node.
 * @num: The node index used for history.
 *
 * Return: The new node added to the list.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	/* Implementation */
}

/**
 * print_list_str - Print only the 'str' element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t print_list_str(const list_t *h)
{
	/* Implementation */
}

/**
 * delete_node_at_index - Delete the node at the given index.
 * @head: Address of the pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	/* Implementation */
}

/**
 * free_list - Free all nodes of a list.
 * @head_ptr: Address of the pointer to the head node.
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	/* Implementation */
}

