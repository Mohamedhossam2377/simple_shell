#include "shell.h"
/**
 * list_length - length of list
 *
 * @ptr: pointer of first node
 *
 * Return: size of list
 */
size_t list_length(const list_t *ptr)
{
	size_t i = 0;

	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

/**
 * list_of_strings- array of strings
 *
 * @ptr_head: pointer of first node
 *
 * Return: array of strings
 */
char **list_of_strings(list_t *ptr_head)
{
	list_t *node = ptr_head;
    size_t i = list_length(ptr_head), j;
    char **arr_strs;
    char *str;

    if (!ptr_head || !i)
        return (NULL);
    arr_strs = malloc(sizeof(char *) * (i + 1));
    if (!arr_strs)
        return (NULL);
    for (i = 0; node; node = node->next, i++)
    {
        str = malloc(str_len(node->str) + 1);
        if (!str)
        {
            for (j = 0; j < i; j++)
                free(arr_strs[j]);
            free(arr_strs);
            return (NULL);
        }

        str = str_cpy(str, node->str);
        arr_strs[i] = str;
    }
    arr_strs[i] = NULL;
    return (arr_strs);
}

/**
 * print_list - print all element in list_t
 * 
 * @ptr_head: pointer of first node
 * 
 * Return: size of list
 */
size_t print_list(const list_t *ptr_head)
{
    size_t i = 0;

    while (ptr_head)
    {
        _puts(conv_num(ptr_head->num, 10, 0));
        put_char(':');
        put_char(' ');
        _puts(ptr_head->str ? ptr_head->str : "(nil)");
        _puts("\n");
        ptr_head = ptr_head->next;
        i++;
    }
    return (i);
}

/**
 * node_starts_with_text - node starts with text
 * 
 * @node: pointer of list head
 * @text: string to match
 * @ch: character
 * 
 * Return: match node or null
 */
list_t *node_starts_with_text(list_t *node, char *text, char ch)
{
    char *pt = NULL;

    while (node)
    {
        pt = begins_with(node->str, text);
        if (pt && ((ch == -1) || (*pt == ch)))
            return (node);
        node = node->next;
    }
    return (NULL);
}

/**
 * get_node_ind - gets the index of node
 * 
 * @ptr_head: pointer to head
 * @node: pointer to node
 * 
 * Return: index of node or -1
 */
ssize_t get_node_ind(list_t *ptr_head, list_t *node)
{
    size_t i = 0;

    while (ptr_head)
    {
        if (ptr_head == node)
            return (i);
        ptr_head = ptr_head->next;
        i++;
    }
    return (-1);
}
