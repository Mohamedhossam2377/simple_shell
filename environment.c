#include "shell.h"

/**
 * my_env - prints the current environment
 *
 * @info: structure containing potential arguments.
 *
 * Return: 0
*/

int my_env(info_t *info)
{
	print_str_list(info->env);
	return (0);
}

/**
 * get_env - gets value of an environ variable
 *
 * @info: Structure containing potential arguments.
 * @name: env var name
 *
 * Return: the value of environ
*/

char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *pt;


	while (node)
	{
		pt = begins_with(node->str, name);
		if (pt && *pt)
			return (pt);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_set_env - initialize a new environment variable.
 *
 * @info: Structure containing potential arguments.
 *
 * Return: 0.
*/

int my_set_env(info_t *info)
{
	if (info->argc != 3)
	{
		e_puts("incorrect number of arguments\n");
		return (1);
	}
	if (set_env (info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unset_env - it removes an environment variable
 *
 * @info: structure containing potential arguments.
 *
 * Return: 0
*/

int my_unset_env(info_t *info)
{
	int i;
	
	if (info->argc == 1)
	{
		e_puts("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unset_env(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populate enviroment test
 *
 * @info: structure containing potential argument. used to maintain
 *         constant function prototype.
 *
 * Return: always 0
*/
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * get_environ - the string array copy of our environ
 * @info: Structure containing potential arguments.
 *
 * Return: returns the string array
*/

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ= list_of_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * unset_env - Remove an enviroment variable
 *
 * @info: Structure containing potential arguments.
 * @var: the string  env var property
 * Return: 1 on delete, 0 otherwise
*/

int unset_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *pt;
	if (!node || !var)
		return (0);

	while (node)
	{
		pt = begins_with(node->str, var);
		if (pt && *pt == '=')
		{
			info->env_changed = del_node_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}
/**
 * set_env - Initialize a new environment variable,or
 *          modify an existing one
 * @info: Structure containing potential arguments. used to maintain
 *             constant function prototype.
 * @var: the string env var property
 * @value: the string env var property
 * Return: Always 0
*/

int set_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *pt;

	if (!var || !value)
		return (0);
	buf = malloc(str_len(var) + s;tr_len(value) + 2)
		if (!buf)
			return (1);
	str_cpy(buf, var);
	str_cat(buf, "=");
	str_cat(buf, value);
	node = info->env;
	while (node)
	{
		 pt = begins_with(node->str, var);
		 if (pt && *pt == '=')
		 {
			 free(node->str);
			 node->str = buf;
			 info->env_changed = 1;
			 return (0);
		 }
		 node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
