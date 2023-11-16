#include "shell.h"

/**
 * **str_tow1 - split strings to words and ignore repeated delimiters
 * 
 * @str: string
 * @del: delimeter
 * 
 * Return: pointer to array of strings
 */
char **str_tow1(char *str, char *del)
{
    int i, j, k, m;
    int num = 0;
    char **ptr;

    if (str == NULL || str[0] == 0)
        return (NULL);
    if (!del)
        del = " ";
    for (i = 0; str[i] != '\0'; i++)
        if (!is_delimeter(str[i], del) && (is_delimeter(str[i + 1], del) || !str[i + 1]))
            num++;
    
    if (num == 0)
        return (NULL);
    ptr = malloc((1 + num) * sizeof(char *));
    if (!ptr)
        return (NULL);
    for (i = 0, j = 0; j < num; j++)
    {
        while (is_delimeter(str[i], del))
            i++;
        k = 0;
        while (!is_delimeter(str[i + k], del) && str[i + k])
            k++;
        ptr[j] = malloc((k + 1) * sizeof(char));
        if (!ptr[j])
        {
            for (k = 0; k < j; k++)
                free(ptr[k]);
            free(ptr);
            return (NULL);
        }
        for (m = 0; m < k; m++)
            ptr[j][m] = str[i++];
        ptr[j][m] = 0;
    }
    ptr[j] = NULL;
    return (ptr);
}

/**
 * **str_tow2 - split strings to words 
 * 
 * @str: string
 * @del: delimeter
 * 
 * Return: pointer to array of strings
 */
char **str_tow2(char *str, char del)
{
    int i, j, k, m;
    int num = 0;
    char **ptr;

    if (str == NULL || str[0] == 0)
        return (NULL);
    for (i = 0; str[i] != '\0'; i++)
        if ((str[i] != del && str[i + 1] == del) ||
            (str[i] != del && !str[i + 1]) || str[i + 1] == del)
            num++;
    if (num == 0)
        return (NULL);
    ptr = malloc((1 + num) * sizeof(char *));
    if (!ptr)
        return (NULL);
    for (i = 0, j = 0; j < num; j++)
    {
        while (str[i] == del && str[i] != del)
            i++;
        k = 0;
        while (str[i + k] != del && str[i + k] && str[i + k] != del)
            k++;
        ptr[j] = malloc((k + 1) * sizeof(char));
        if (!ptr[j])
        {
            for (k = 0; k < j; k++)
                free(ptr[k]);
            free(ptr);
            return (NULL);
        }
        for (m = 0; m < k; m++)
            ptr[j][m] = str[i++];
        ptr[j][m] = 0;
    }
    ptr[j] = NULL;
    return (ptr);
}
