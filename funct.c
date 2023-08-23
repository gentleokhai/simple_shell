#include "myheader.h"

/**
 *_strspn - This function gets the length of substring
 *@str1: string to be searched
 *@str2: string to be used
 *
 *Return: number of bytes in the initial segment of 5
 */

int _strspn(char *str1, char *str2)
{
	int i = 0;
	int match = 0;

	while (str1[i] != '\0')
	{
		if (_strchr(str2, str1[i]) == NULL)
			break;
		match++;
		i++;
	}
	return (match);
}

/**
 *_strcspn - computes part of strg1 which consists of characters not in strg2
 *@str1: string to be searched
 *@str2: string to be used
 *
 *Return: index at which a char in strg1 exists in strg2
 */
int _strcspn(char *str1, char *str2)
{
	int len = 0, boo;

	for (boo = 0; str1[boo] != '\0'; boo++)
	{
		if (_strchr(str2, str1[boo]) != NULL)
			break;
		len++;
	}
	return (len);
}

/**
 * get_func - retrieves a funct.
 * @command: strg to check against the mapping.
 *
 * Return: null if failure
 */
void (*get_func(char *command))(char **)
{
    /*Declaration*/
	int strg;
	function_map mapping[] = {
		{"env", env}, {"exit", quit}
	};

	for (strg = 0; strg < 2; strg++)
	{
		if (_strcmp(command, mapping[strg].command_name) == 0)
			return (mapping[strg].func);
	}
	return (NULL);
}
