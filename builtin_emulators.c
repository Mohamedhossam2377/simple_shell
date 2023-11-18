#include "shell.h"

/**
 * my_exit - exits the shell
 * 
 * @info: structure containing potential arguments.
 * 
 * Return: exits with a given exit status (0)
 */

int my_exit(info_t *info)
{
    int check_exit;

    if (info->argv[1]) 
    {
        check_exit = err_atoi(info->argv[1]);
        if (check_exit == -1)
        {
            info->status = 2; 
            prints_error(info, "illegal number: ");
            e_puts(info->argv[1]);
            e_putchar('\n');
            return (1);
        }
        info->err_num = err_atoi(info->argv[1]);
        return (-2); 
    }
    info->err_num = -1;
    return(-2);
}

/**
 * my_cd - changes the current directory
 * 
 * @info: structure containing potential arguments.
 * 
 * Return: 0
 */
 int my_cd(info_t *info) // pwd = /folder1, oldpwd /parent/ folder1
{
     char *s, *dirc, buffer[1024];
     int chdir_ret;

     s = getcwd(buffer, 1024);
     if (!s)
         _puts("TODO: >>getcwd failure emsg here<<\n");
     if (!info->argv[1])
     {
         dirc = get_env(info, "HOME=");
         if (!dirc)
             chdir_ret = chdir((dirc = get_env(info, "PWD=")) ? dirc : "/");
         else
             chdir_ret = chdir(dirc);
     }
     else if (str_cmp(info->argv[1], "-") == 0)
     {
         if (!get_env(info, "OLDPWD="))
         {
             _puts(s);
             put_char('\n');
             return (1);
         }
         _puts(get_env(info, "OLDPWD=")), put_char('\n');
         chdir_ret = chdir((dirc = get_env(info, "OLDPWD=")) ? dirc : "/");
     }
     else
         chdir_ret = chdir(info->argv[1]);
     if (chdir_ret == -1)
     {
         prints_error(info, "cannot cd to");
         e_puts(info->argv[1]), e_putchar('\n');
     }
     else
     {
         set_env(info, "OLDPWD", get_env(info, "PWD="));
         set_env(info, "PWD", getcwd(buffer, 1024));
     }
     return (0);
}

/**
 * my_help - help call works
 * 
 * @info: structure containing potential arguments.
 * 
 * Return: always 0
 */

int my_help(info_t *info)
{
    char **arg_arr;

    arg_arr = info->argv;
    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*arg_arr);
    return (0);
}

/**
 * my_history - displays the history list.
 * 
 * @info: Structure containing potential arguments.
 * 
 *  Return:0
 */
int my_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * 
 * @info: parameter struct
 * @str: the string
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *pt, ch;
	int ret;

	pt = str-chr(str, '=');
	if (!pt)
		return (1);
	ch = *pt;
	*pt = 0;
	ret = del_node_index(&(info->alias),
		get_node_ind(info->alias, node_starts_with_text(info->alias, str, -1)));
	*pt = ch;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *pt;

	pt = str_chr(str, '=');
	if (!pt)
		return (1);
	if (!*++pt)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * 
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *pt = NULL, *a = NULL;

	if (node)
	{
		pt = str_chr(node->str, '=');
		for (a = node->str; a <= pt; a++)
			put_char(*a);
		put_char('\'');
		_puts(pt + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - mimics the alias builtin (man alias)
 * 
 * @info: Structure containing potential arguments.
 * 
 *  Return: Always 0
 */
int my_alias(info_t *info)
{
	int i = 0;
	char *pt = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		pt = str_chr(info->argv[i], '=');
		if (pt)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with_text(info->alias, info->argv[i], '='));
	}

	return (0);
}
