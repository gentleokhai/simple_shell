#include "myheader.h"

/**
 * Auth: OKHAI GENTLE
 *
 * Description:
 * the extended functions for main.c
 */

/**
 * _getenv - This function will get environment variables value
 * @name: name of the var
 *
 * Return: the value of the variable as a string
 */

char *_getenv(char *name)
{
	char *name_copy;
	char **my_env;
	char *pair_pt;
	
	for (my_env = environ; *my_env != NULL; my_env++)
	{
		for (pair_pt = *my_env, name_copy = name;
		     *pair_pt == *name_copy; pair_pt++, name_copy++)
		{
			if (*pair_pt == '=')
				break;
		}
		if ((*pair_pt == '=') && (*name_copy == '\0'))
			return (pair_pt + 1);
	}
	return (NULL);
}

/**
 * check_path - This function will check if a command is in the PATH
 * @command: command to be used
 *
 * Return: path where the command is in, NULL if not set up
 */

char *check_path(char *command)
{
	int i;
	char **path_array = NULL;
	char *temp, *temp2, *path_cpy;
	char *pth = _getenv("PATH");

	if (pth == NULL || _strlen(pth) == 0)
		return (NULL);
	path_cpy = malloc(sizeof(*path_cpy) * (_strlen(pth) + 1));
	_strcpy(pth, path_cpy);
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

/** parse_command - Function determines the type of the command
 * @command: command to be parsed
 *
 * Return: constant representing the type of the command
 * Description -
 * 		 EXTERNAL_COMMAND (1) represents commands example /bin/ls
 *		 INTERNAL_COMMAND (2) represents commands example exit, env
 *		 PATH_COMMAND (3) represents command in the PATH example ls
 *		 INVALID_COMMAND (-1) represents invalid commands
 */

int parse_command(char *command)
{
	int b;
	char *path = NULL;
	char *internal_command[] = {"env", "exit", NULL};

	for (b = 0; command[b] != '\0'; b++)
	{
		if (command[b] == '/')
			return (EXTERNAL_COMMAND);
	}
	for (b = 0; internal_command[b] != NULL; b++)
	{
		if (_strcmp(command, internal_command[b]) == 0)
			return (INTERNAL_COMMAND);
	}
	/* @check_path - To check if a command is in the PATH */
	path = check_path(command);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}

/**
 * execute_command - This function executes a command based on it's type!
 * @tok_cmd: tokenized form of the command .
 * @cmd_typ: type of the command!
 *
 * Return: void
 */
void execute_command(char **tok_cmd, int cmd_typ)
{
	void (*func)(char **command);

	if (cmd_typ == EXTERNAL_COMMAND)
	{
		if (execve(tok_cmd[0], tok_com, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (cmd_typ == PATH_COMMAND)
	{
		if (execve(check_path(tok_cmd[0]), tok_cmd, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (cmd_typ == INTERNAL_COMMAND)
	{
		func = get_func(tok_cmd[0]);
		func(tok_cmd);
	}
	if (cmd_typ == INVALID_COMMAND)
	{
		print(shell_name, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(tok_cmd[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		status = 127;
	}
}

/**
 * get_func - This function retrieves a function based on the command given and a mapping.
 * @command: string to check against the mapping.
 *
 * Return: pointer to proper function, or null on fail.
 */

void (*get_func(char *command))(char **)
{
	int ii;
	function_map mapping[] = {
		{"env", env}, {"exit", quit}
	};

	for (ii = 0; ii < 2; ii++)
	{
		if (_strcmp(command, mapping[i].command_name) == 0)
			return (mapping[ii].func);
	}
	return (NULL);
}
