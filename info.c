#include "shell.h"

/**
 * clear_info_init - initializes info_t struct
 *
 * @info: struct address
 *
 * Return: nothing
 */
void clear_info_init(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info_init - initializes info_t struct
 *
 * @info: struct address
 * @av: argument vector
 *
 * Return: nothing
 */
void set_info_init(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_tow1(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = str_dup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}
/**
 * free_info - frees info_t
 *
 * @info: struct address
 * @all_fields: true if freeing all fields
 */

void free_info(info_t *info, int all_fields)
{
	f_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all_fields)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		f_free(info->environ);
			info->environ = NULL;
		b_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		put_char(BUF_FLUSH);
	}
}
