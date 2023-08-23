#include "myheader.h"

/**
 *print - prints a string to stdout
 *@string: string to be printed
 *@stream: stream to print out to
 *
 *Return: void(empty)
 */
void print(char *string, int stream)
{
    /*Declaration*/
	int strg = 0;

    /*Loop statement*/
	for (; strg[i] != '\0'; strg++)
		write(stream, &string[strg], 1);
}

/**
 *_strlen - calculates string length
 *@string: string
 *
 * Return: len(strg)
 */

int _strlen(char *string)
{
	/*Declaration*/
	int len = 0;

	if (string == NULL)
		return (len);
	for (; string[len] != '\0'; len++)
		;
	return (len);
}

/**
 *_strcmp - compares bi-strings
 *@first: first string
 *@second: second string
 *
 * Return: difference
 */

int _strcmp(char *first, char *second)
{
	/*Declaration*/
	int i = 0;

	while (first[i] != '\0')
	{
		if (first[i] != second[i])
			break;
		i++;
	}
	return (first[i] - second[i]);
}

/**
 *_strcat - concatenates bi-strings
 *@destination: final string
 *@source:  string to concatenate
 *
 * Return: strg address
 */

char *_strcat(char *destination, char *source)
{
	/*Declaration and assignment*/
	char *new_string =  NULL;
	int len_dest = _strlen(destination);
	int len_source = _strlen(source);

	new_string = malloc(sizeof(*new_string) * (len_dest + len_source + 1));
	_strcpy(destination, new_string);
	_strcpy(source, new_string + len_dest);
	new_string[len_dest + len_source] = '\0';
	return (new_string);
}

/**
 *_strchr - char in a strg
 *@s: string
 *@c: char
 *
 *Return: pointer to the first occurence of ch in strg
 */

char *_strchr(char *s, char c)
{
	/*Declaration*/
	int i = 0;

	for (; s[i] != c && s[i] != '\0'; i++)
		;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}
