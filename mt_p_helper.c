#include "mutashell.h"
/**
 * mt_printf - a function that writes to the console
 * @wyz: points to the string
 * Return: the number of strings or -1 on error
 */
int mt_printf(char *wyz)
{
	return (write(STDOUT_FILENO, wyz, str_length(wyz)));
}
