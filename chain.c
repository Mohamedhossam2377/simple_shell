#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * 
 * @info: the parameter struct
 * @buf: the char buffer
 * @ptr: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *ptr)
{
	size_t j = *ptr;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * 
 * @info: the parameter struct
 * @buf: the char buffer
 * @ptr: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: nothing
 */
void check_chain(info_t *info, char *buf, size_t *ptr, size_t i, size_t len)
{
	size_t j = *ptr;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*ptr = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with_text(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = str_chr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = str_dup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * 
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!str_cmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				str_dup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(conv_num(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with_text(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				str_dup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], str_dup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * 
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
