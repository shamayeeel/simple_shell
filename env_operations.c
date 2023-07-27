#include "shell.h"

/**
 * get_environ - Get a copy of the environment variables as a string array.
 * @info: Structure containing potential arguments.
 *
 * Return: The pointer to the string array of environment variables.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_env_var - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * @var: The name of the environment variable to be removed.
 *
 * Return: 1 if the variable is deleted, 0 otherwise.
 */
int unset_env_var(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
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
 * set_env_var - Set or modify an environment variable.
 * @info: Structure containing potential arguments.
 * @var: The name of the environment variable to be set or modified.
 * @value: The value to be assigned to the environment variable.
 *
 * Return: 0 on success, 1 on memory allocation failure.
 */
int set_env_var(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
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

