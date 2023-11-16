#include "shell.h"

/**
 * str_dup - duplicates a string
 *
 * @str: string
 *
 * Return: pointer to new string
 */
char *str_dup(const char *str)
{
    int len = 0;
    char *ptr;

    if (str == NULL)
        return (NULL);
    while (*str++)
        len++;
    ptr = malloc(sizeof(char) * (len + 1));
    if (!ptr)
        return (NULL);
    for (len++; len--;)
        ptr[len] = *--str;
    return (ptr);
}

/**
 * _puts - print a string
 *
 * @str: string
 *
 * Return: nothing
 */
void _puts(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        put_char(str[i]);
        i++;
    }
}

/**
 * put_char - print charcter
 *
 * @ch: character
 *
 * Return: character
 */
int put_char(char ch)
{
    static int i;
    static char buff[WRITE_BUF_SIZE];

    if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buff, i);
        i = 0;
    }
    if (ch != BUF_FLUSH)
        buff[i++] = ch;
    return (i);
}

/**
 * str_ncpy - copy a string
 *
 * @str1: first string
 * @str2: second string
 * @num: amount of characters to be copied
 *
 * Return: pointer to new string
 */
char *str_ncpy(char *str1, char *str2, int num)
{
    int i, j;
    char *ptr = str1;

    i = 0;
    while (str2[i] != '\0' && i < num - 1)
    {
        str1[i] = str2[i];
        i++;
    }
    if (i < num)
    {
        j = i;
        while (j < num)
        {
            str1[j] = '\0';
            j++;
        }
    }
    return (ptr);
}

/**
 * str_ncat - concatentate two strings
 *
 * @str1: first string
 * @str2: second string
 * @num: amount of characters to be concatentate
 *
 * Return: pointer to new string
 */
char *str_ncat(char *str1, char *str2, int num)
{
    int i, j;
    char *ptr = str1;

    i = 0;
    j = 0;
    while (str1[i] != '\0')
        i++;
    while (str2[j] != '\0' && j < num)
    {
        str1[i] = str2[j];
        i++;
        j++;
    }
    if (j < num)
        str1[i] = '\0';
    return (ptr);
}

/**
 * str_chr - locates a char in string
 *
 * @str: string
 * @ch: character to look for
 *
 * Return: a pointer to located area
 */
char *str_chr(char *str, char ch)
{
    do {
        if (*str == ch)
            return (str);
    } while (*str++ != '\0');

    return (NULL);
}
