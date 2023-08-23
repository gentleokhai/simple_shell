#include "myheader.h"

/**
 * ctrl_c_handler - deals with the signal raised by CTRL-C
 * @signum: signal no
 *
 * Return: nothing
 */
void ctrl_c_handler(int signum)
{
	if (signum == SIGINT)
		print("\n($) ", STDIN_FILENO);
}

/**
 *_strcpy - copies a strg
 *@source: source
 *@dest: destination
 *
 * Return: nothing
 */
void _strcpy(char *source, char *dest)
{
	int strg = 0;

	for (; source[strg] != '\0'; strg++)
		dest[strg] = source[strg];
	dest[strg] = '\0';
}

/**
 *remove_newline - removes new line from strg
 *@str: strg
 *
 *
 *Return: void
 */

void remove_newline(char *str)
{
	int strg = 0;

	while (str[strg] != '\0')
	{
		if (str[strg] == '\n')
			break;
		strg++;
	}
	str[strg] = '\0';
}

/**
 * _atoi - changes a string to an integer
 * @s: the string to be changed
 *
 * Return: the converted int
 */
int _atoi(char *s)
{
    /*Declaration and a do while loop*/
	unsigned int n = 0;

	do {
		if (*s == '-')
			return (-1);
		else if ((*s < '0' || *s > '9') && *s != '\0')
			return (-1);
		else if (*s >= '0'  && *s <= '9')
			n = (n * 10) + (*s - '0');
		else if (n > 0)
			break;
	} while (*s++);
	return (n);
}

/**
 * remove_comment - removes/ignores everything after a '#' char
 * @input: input to be used
 *
 * Return: void
 */
void remove_comment(char *input)
{
	int cc = 0;

	if (input[cc] == '#')
		input[cc] = '\0';
	while (input[cc] != '\0')
	{
		if (input[cc] == '#' && input[cc - 1] == ' ')
			break;
		cc++;
	}
	input[cc] = '\0';
}
