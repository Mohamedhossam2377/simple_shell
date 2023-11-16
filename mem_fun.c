#include "shell.h"

/**
 * *mem_set - fill memory with constant byte
 * 
 * @ptr: pointer to memory area
 * @by: byte
 * @num: num of bytes to be filled
 * 
 * Return: pointer to memory area
 */
char *mem_set(char *ptr, char by, unsigned int num)
{
    unsigned int i;

    for (i = 0; i < num; i++)
        ptr[i] = by;
    return (ptr);
}

/**
 * f_free - free string of strings
 * 
 * @strs: string of strings
 * 
 * Return: nothing
 */
void f_free(char **strs)
{
    char **ptr = strs;

    if (!strs)
        return;
    while (*strs)
        free(*strs++);
    free(ptr);
}

/**
 * *_realloc - reallocate a memory
 * 
 * @ptr: pointer to previous mallocated memory
 * @pre_size: previous size byte
 * @new_size: new size byte
 * 
 * Return: pointer to reallaocate memory
 */
void *_realloc(void *ptr, unsigned int pre_size, unsigned int new_size)
{
    char *pt;

    if (!ptr)
        return (malloc(new_size));
    if (!new_size)
        return (free(ptr), NULL);
    if (new_size == pre_size)
        return (ptr);
    
    pt = malloc(new_size);
    if (!pt)
        return (NULL);
    
    pre_size = pre_size < new_size ? pre_size : new_size;
    while (pre_size--)
        pt[pre_size] = ((char *)ptr)[pre_size];
    free(ptr);
    return (pt);
}

/**
 * b_free - free pointer
 * 
 * @ptr: pointer
 * 
 * Return: 1 if free, otherwise 0
 */
int b_free(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
        return (1);
    }
    return (0);
}
