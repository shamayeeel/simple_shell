/* File Name: memory_utils.c */

/**
 * free_and_null - Frees a pointer and sets it to NULL.
 * @pp: Address of the pointer to free.
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_and_null(void **pp)
{
    if (pp && *pp)
    {
        free(*pp);
        *pp = NULL;
        return (1);
    }
    return (0);
}

