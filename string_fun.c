#include "shell.h"

/**
 * str_len - length of a string
 * 
 * @st: string
 * 
 * Return: length
 */
int str_len(char *str)
{
    int i = 0;

    if (!str)
        return (0);

    while (*str++)
        i++;
    return (i);
}

/**
 * str_cmp - comparison between two strings
 * 
 * @str1: first string
 * @str2: second string
 * 
 * Return: zero if str1 == str2, positive if str1 > str2, negative if str1 < str2
 */
int str_cmp(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return (*str1 - *str2);
        str1++;
        str2++;
    }
    if (*str1 == *str2)
        return (0);
    else
        return (*str1 < *str2 ? -1 : 1);
}

/**
 * begins_with - check if beg_str starts with str
 * 
 * @str: string to search in
 * @beg_str: string to find
 * 
 * Return: address of next char of str or NULL
 */
char *begins_with(const char *str, const char *beg_str)
{
    while (*beg_str)
        if (*beg_str++ != *str++)
            return (NULL);
    return ((char *)str);
}

/**
 * str_cat - concatenates two strings
 * 
 * @str1: first string
 * @str2: second string
 * 
 * Return: pointer to new string
 */
char *str_cat(char *str1, char *str2)
{
    char *ptr = str1;

    while (*str1)
        str1++;
    while (*str2)
        *str1++ = *str2++;
    *str1 = *str2;
    return (ptr);
}

/**
 * str_cpy - copy a string
 * 
 * @str1: first string
 * @str2: second string
 * 
 * Return: pointer of new string
 */
char *str_cpy(char *str1, char *str2)
{
    int i = 0;

    if (str1 == str2 || str2 == 0)
        return (str1);
    while (str2[i])
    {
        str1[i] = str2[i];
        i++;
    }
    str1[i] = 0;
    return (str1);
}
