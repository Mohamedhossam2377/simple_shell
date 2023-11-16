#include "shell.h"

/**
 * interactive_mode - if shell is interactive mode return true
 * 
 * @ptr: struct address
 * 
 * Return: 1 if interactive mode, if else return 0
 */
int interactive_mode(info_t *ptr)
{
    return (isatty(STDIN_FILENO) && ptr->readfd <= 2);
}

/**
 * is_delimeter - check if character is delimeter
 * 
 * @ch: character
 * @del: delimeter
 * 
 * Return: 1 if true, if false return 0
 */
int is_delimeter(char ch, char *del)
{
    while (*del)
        if (*del++ == ch)
            return (1);
    return (0);
}

/**
 * is_alpha - check if character is alphabetic
 * 
 * @ch: character
 * 
 * Return: 1 if true, if false return 0
 */
int is_alpha(int ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return (1);
    else
        return (0);
}

/**
 * _atoi - convert string to int
 * 
 * @str: string
 * 
 * Return: number or 0 if no numbers in string
 */
int _atoi(char *str)
{
    int i, output;
    int sign = 1;
    int flag = 0;
    unsigned int result = 0;

    for (i = 0; str[i] != '\0' && flag != 2; i++)
    {
        if (str[i] == '-')
            sign *= -1;
        
        if (str[i] >= '0' && str[i] <= '9')
        {
            flag = 1;
            result *= 10;
            result += (str[i] - '0');
        }
        else if (flag == 1)
            flag = 2;
    }

    if (sign == -1)
        output = -result;
    else
        output = result;
    
    return (output);
}

/**
 * err_atoi - convert string to int
 * 
 * @str: string
 * 
 * Return: number or 0 if no numbers in string
 */
int err_atoi(char *str)
{
    int i = 0;
    unsigned long int result = 0;

    if (*str == '+')
        str++;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            result *= 10;
            result += (str[i] - '0');
            if (result > INT_MAX)
                return (-1);
        }
        else
            resturn (-1);
    }
    return (result);
}

/**
 * prints_error - print error message
 * 
 * @str: string
 * 
 * Return: number or 0 if no numbers in string
 */
void prints_error(info_t *info, char *str_err)
{
    _eputs(info-> fname);
    _eputs(": ");
    prints_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(str_err);
}

/**
 * prints_d - print number
 * 
 * @input: input
 * @file_d: file descriptor to write
 * 
 * Return: number of printer character
 */
int prints_d(int input, int file_d)
{
    int (*__putchar)(char) = put_char;
    int i, sum = 0;
    unsigned int _abs_, current;

    if (file_d == STDERR_FILENO)
        __putchar = e_putchar;
    if (input < 0)
    {
        _abs_ = -input;
        __putchar('-');
        sum++;
    }
    else
        _abs_ = input;
    current = _abs_;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (_abs_ / i)
        {
            __putchar('0' + current / i);
            sum++;
        }
        current %= i;
    }
    __putchar('0' + current);
    sum++;

    return (sum);
}

/**
 * conv_num - convert function
 * 
 * @num: number
 * @b: base
 * @flag: flag argument
 * 
 * Return: string
 */
char *conv_num(long int num, int b, int flag)
{
    static char *arr;
    static char buff[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flag & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }
    arr = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buff[49];
    *ptr = '\0';

    do {
        *--ptr = arr[n % b];
        n /= b;
    } while (n != 0);

    if (sign)
        *--ptr = sign;
    return (ptr);
}

/**
 * rem_comment - replace # to '\0'
 * 
 * @buff: addres to modify
 * 
 * Return: 0
 */
void rem_comment(char *buff)
{
    int i;

    for (i = 0; buff[i] != '\0'; i++)
        if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
        {
            buff[i] = '\0';
            break;
        }
}
