#include "shell.h"

/**
 * e_puts - print string
 * 
 * @str: string
 * 
 * Return: nothing
 */
void e_puts(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        e_putchar(str[i]);
        i++;
    }
}

/**
 * e_putchar - write character to stderr
 * 
 * @ch: character
 * 
 * Return: 1 on success, -1 on error
 */
int e_putchar(char ch)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (ch != BUF_FLUSH)
        buf[i++] = ch;
    return (1);
}

/**
 * put_fd - write character to given fd
 * 
 * @ch: character
 * @fd: filedescriptor to write
 * 
 * Return: 1 on success, -1 on error
 */
int put_fd(char ch, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (ch != BUF_FLUSH)
        buf[i++] = ch;
    return (1);
}

/**
 * puts_fd - print string
 * 
 * @str: string
 * @fd: filedescriptor to write
 * 
 * Return: number of characters
 */
int puts_fd(char *str, int fd)
{
    int i = 0;

    if (!str)
        return (0);
    while (*str)
    {
        i += put_fd(*str++, fd);
    }
    return (i);
}
