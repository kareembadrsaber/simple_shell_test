#include "shell.h"

/**
 * env_get_key - Retrieves the value of an environment variable.
 * @key: The environment variable of interest.
 * @data: A pointer to the program's data structure.
 * Return: A pointer to the value of the variable or NULL if it doesn't exist.
 */
char *env_get_key(char *key, data_of_program *data)
{
	int i, key_length = 0;

	
	if (key == NULL || data->env == NULL)
		return (NULL);

	
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{
			return (data->env[i] + key_length + 1);
		}
	}
	
	return (NULL);
}

/**
 * env_set_key - Overwrites the value of the environment variable or creates
 * it if it does not exist.
 * @key: Name of the variable to set.
 * @value: New value.
 * @data: A pointer to the program's data structure.
 * Return: 1 if the parameters are NULL, 2 if there is an error, or 0 if success.
 */
int env_set_key(char *key, char *value, data_of_program *data)
{
	int i, key_length = 0, is_new_key = 1;

	
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{
			is_new_key = 0;
			
			free(data->env[i]);
			break;
		}
	}
	
	data->env[i] = str_concat(str_duplicate(key), "=");
	data->env[i] = str_concat(data->env[i], value);

	if (is_new_key)
	{
	
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - Removes a key from the environment.
 * @key: The key to remove.
 * @data: A pointer to the program's data structure.
 * Return: 1 if the key was removed, 0 if the key does not exist.
 */
int env_remove_key(char *key, data_of_program *data)
{
	int i, key_length = 0;

	
	if (key == NULL || data->env == NULL)
		return (0);

	
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{
			free(data->env[i]);

			
			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - Displays the current environment variables.
 * @data: A pointer to the program's data structure.
 * Return: None.
 */
void print_environ(data_of_program *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
}
