#include "myheader.h"

/**
 * quit - ends the process
 * @tokenized_command: command entered
 *
 * Return: void
 */
void quit(char **tokenized_command)
{
    /*The basic declarations*/
	int num_tok = 0, ag;

	for (; tokenized_command[num_tok] != NULL; num_tok++)
		;
	/*Control flow freeing memory*/
	if (num_tok == 1)
	{
		free(tokenized_command);
		free(line);
		free(commands);
		exit(status);
	}
	else if (num_tok == 2)
	{
		ag = _atoi(tokenized_command[1]);
		if (ag == -1)
		{
			print(shell_name, STDERR_FILENO);
			print(": 1:->exit:-> Illegal number:-> ", STDERR_FILENO);
			print(tokenized_command[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			status = 2;
		}
		else
		{
			free(line);
			free(tokenized_command);
			free(commands);
			exit(ag);
		}
	}
	else
		print("$-> EXIT DOESN'T ACCEPT MORE THAN AN INPUT\n", STDERR_FILENO);
}

/**
 * _getenv - The function collects the value of the environment variable
 * @name: name of the environment
 *
 * Return: the value of the variable as a string
 */
char *_getenv(char *name)
{
	/*The declarations*/
	char **my_environ;
	char *pair_pt;
	char *name_cp;
	/*For loop that nests*/
	for (my_environ = environ; *my_environ != NULL; my_environ++)
	{
		for (pair_pt = *my_environ, name_cp = name;
		     *pair_pt == *name_cp; pair_pt++, name_cp++)
		{
			if (*pair_pt == '=')
				break;
		}
		if ((*pair_pt == '=') && (*name_cp == '\0'))
			return (pair_pt + 1);
	}
	return (NULL);
}

/**
 * check_path - checks if a command is found in the PATH
 * @command: command to be used
 *
 * Return: path where the command is found in, NULL if not found
 */
char *check_path(char *command)
{
	char **path_array = NULL;
	char *temp, *temp2, *path_cpy;
	char *path = _getenv("PATH");
	int i;

	if (path == NULL || _strlen(path) == 0)
		return (NULL);
	path_cpy = malloc(sizeof(*path_cpy) * (_strlen(path) + 1));
	_strcpy(path, path_cpy);
	path_array = tokenizer(path_cpy, ":");
	for (i = 0; path_array[i] != NULL; i++)
	{
		temp2 = _strcat(path_array[i], "/");
		temp = _strcat(temp2, command);
		if (access(temp, F_OK) == 0)
		{
			free(temp2);
			free(path_array);
			free(path_cpy);
			return (temp);
		}
		free(temp);
		free(temp2);
	}
	free(path_cpy);
	free(path_array);
	return (NULL);
}

/**
 *env - push the current_environnement to the standard ouput.
 *@tokenized_command: command entered
 *
 *Return: void
 */

void env(char **tokenized_command __attribute__((unused)))
{
	int d;

	for (d = 0; environ[d] != NULL; d++)
	{
		print(environ[d], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}
