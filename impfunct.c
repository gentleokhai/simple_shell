#include "myheader.h"

/**
 * _realloc - reallocates
 * @ptr: pointer
 * @old_size: size of ptr
 * @new_size: size of the new memory to be allocated
 *
 * Return: pointer to the address of the new memory block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *temp_block;
	unsigned int i;

	if (ptr == NULL)
	{
		temp_block = malloc(new_size);
		return (temp_block);
	}
	else if (new_size == old_size)
		return (ptr);
	else if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		temp_block = malloc(new_size);
		if (temp_block != NULL)
		{
			for (i = 0; i < min(old_size, new_size); i++)
				*((char *)temp_block + i) = *((char *)ptr + i);
			free(ptr);
			return (temp_block);
		}
		else
			return (NULL);

	}
}

/**
 * tokenizer - tokenizes and stores input in an array
 *@input_string: input
 *@delim: delimiter
 *
 *Return: array of tokens
 */

char **tokenizer(char *input_string, char *delim)
{
	int num_delim = 0;
	char **avv = NULL;
	char *token = NULL;
	char *save_ptr = NULL;

	token = _strtok_r(input_string, delim, &save_ptr);

	while (token != NULL)
	{
		avv = _realloc(avv, sizeof(*avv) * num_delim, sizeof(*avv) * (num_delim + 1));
		avv[num_delim] = token;
		token = _strtok_r(NULL, delim, &save_ptr);
		num_delim++;
	}

	avv = _realloc(avv, sizeof(*avv) * num_delim, sizeof(*avv) * (num_delim + 1));
	avv[num_delim] = NULL;

	return (avv);
}

/**
 *_strtok_r - tokenizes a string
 *@string: string to be tokenized
 *@delim: delimiter to be used to tokenize the string
 *@save_ptr: pointer to be used to keep track of the next token
 *
 *Return: The next available token
 */
char *_strtok_r(char *string, char *delim, char **save_ptr)
{
    /*Declaration*/
	char *finish;
    /*control flow statements and body of the function*/
	if (string == NULL)
		string = *save_ptr;

	if (*string == '\0')
	{
		*save_ptr = string;
		return (NULL);
	}

	string += _strspn(string, delim);
	if (*string == '\0')
	{
		*save_ptr = string;
		return (NULL);
	}

	finish = string + _strcspn(string, delim);
	if (*finish == '\0')
	{
		*save_ptr = finish;
		return (string);
	}

	*finish = '\0';
	*save_ptr = finish + 1;
	return (string);
}

/** parse_command - determines the type of the command
 * @command: command to be parsed
 *
 * Return: constant representing the type of the command
 * Description -
 * 		 EXTERNAL_COMMAND (1) > commands like /bin/ls
 *		 INTERNAL_COMMAND (2) -> commands exit, env
 *		 PATH_COMMAND (3) -> commands found in the PATH 
 *		 INVALID_COMMAND (-1) -> invalid commands
 */

int parse_command(char *command)
{
	int i;
	char *internal_command[] = {"env", "exit", NULL};
	char *path = NULL;

	for (i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == '/')
			return (EXTERNAL_COMMAND);
	}
	for (i = 0; internal_command[i] != NULL; i++)
	{
		if (_strcmp(command, internal_command[i]) == 0)
			return (INTERNAL_COMMAND);
	}
	/* @check_path - checks if a command is found in the PATH */
	path = check_path(command);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}

/**
 * execute_command - executes a command based on it's type
 * @tokenized_command: tokenized form of the command
 * @command_type: type of the command
 *
 * Return: nothing
 */
void execute_command(char **tokenized_command, int command_type)
{
	void (*func)(char **command);

	if (command_type == EXTERNAL_COMMAND)
	{
		if (execve(tokenized_command[0], tokenized_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (command_type == PATH_COMMAND)
	{
		if (execve(check_path(tokenized_command[0]), tokenized_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (command_type == INTERNAL_COMMAND)
	{
		func = get_func(tokenized_command[0]);
		func(tokenized_command);
	}
	if (command_type == INVALID_COMMAND)
	{
		print(shell_name, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(tokenized_command[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		status = 127;
	}
}
