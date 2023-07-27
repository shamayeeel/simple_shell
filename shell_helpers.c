#include "shell.h"

/**
 * interactive - Check if the shell is running in interactive mode.
 * @info: Address of the struct containing shell information.
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise.
 */
int interactive(info_t *info)
{
	/* Check if input is coming from a terminal (interactive mode)
	 * and readfd is within valid range.
	 */
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Check if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * Return: 1 if the character is a delimiter, 0 if not.
 */
int is_delim(char c, char *delim)
{
	/* Iterate through the delimiter string and check if the character matches any delimiter. */
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - Check if a character is an alphabetic character.
 * @c: The character to check.
 *
 * Return: 1 if the character is alphabetic, 0 otherwise.
 */
int _isalpha(int c)
{
	/* Check if the character falls within the range of lowercase or uppercase alphabets. */
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Convert a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if there are no numbers in the string, the converted number otherwise.
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	/* Iterate through the string and convert it to an integer. */
	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	/* Apply sign and return the converted integer. */
	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

