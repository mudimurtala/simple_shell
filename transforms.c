#include "mutashell.h"

void resolve_vars(mt_code_info *info);

/**
 * resolve_vars - this function is tasked with expanding vars
 * @info: represents a pointer pointing to the stored info.
 *
 * Return: errno is set, and void is returned
 */
void resolve_vars(mt_code_info *info)
{
	int m, n;

	char phrase[BUFFER_CAPACITY] = {0};
	char increase[BUFFER_CAPACITY]	= {'\0'}, *transient;

	char phrase[BUFFER_CAPACITY] = {0}, increase[BUFFER_CAPACITY] = {'\0'}, *transient;


	if (info->prompt_user == NULL)
		return;
	append_to_buffer(phrase, info->prompt_user);
	for (m = 0; phrase[m]; m++)
		if (phrase[m] == '#')
			phrase[m--] = '\0';
		else if (phrase[m] == '$' && phrase[m + 1] == '?')
		{
			phrase[m] = '\0';
			integerToString(errno, increase, 10);
			append_to_buffer(phrase, increase);
			append_to_buffer(phrase, info->prompt_user + m + 2);
		}
		else if (phrase[m] == '$' && phrase[m + 1] == '$')
		{
			phrase[m] = '\0';
			integerToString(getpid(), increase, 10);
			append_to_buffer(phrase, increase);
			append_to_buffer(phrase, info->prompt_user + m + 2);
		}
		else if (phrase[m] == '$' && (phrase[m + 1] == ' ' || phrase[m + 1] == '\0'))
			continue;
		else if (phrase[m] == '$')
		{
			for (n = 1; phrase[m + n] && phrase[m + n] != ' '; n++)
				increase[n - 1] = phrase[m + n];
			transient = obtain_environment_secret(increase, info);
			phrase[m] = '\0', increase[0] = '\0';
			append_to_buffer(increase, phrase + m + n);
			transient ? append_to_buffer(phrase, transient) : 1;
			append_to_buffer(phrase, increase);
		}
	if (!_strcomp(info->prompt_user, phrase, 0))
	{
		free(info->prompt_user);
		info->prompt_user = _strclone(phrase);
	}
}

/**
 * mt_resolveAlias - this function is tasked with expanding aliases
 * @info: points to the data of the program
 *
 * Return: errno is set appropriately, returns void
 */
void mt_resolveAlias(mt_code_info *info)
{
	int m, n, hasEnlarged = 0;

	char phrase[BUFFER_CAPACITY] = {0}, increase[BUFFER_CAPACITY]
		= {'\0'}, *transient;
	char phrase[BUFFER_CAPACITY] = {0}, increase[BUFFER_CAPACITY] = {'\0'}, *transient;

	if (info->prompt_user == NULL)
		return;

	append_to_buffer(phrase, info->prompt_user);

	for (m = 0; phrase[m]; m++)
	{
		for (n = 0; phrase[m + n] && phrase[m + n] != ' '; n++)
			increase[n] = phrase[m + n];
		increase[n] = '\0';

		transient = mt_findAlias(info, increase);
		if (transient)
		{
			increase[0] = '\0';
			append_to_buffer(increase, phrase + m + n);
			phrase[m] = '\0';
			append_to_buffer(phrase, transient);
			phrase[_strlen(phrase)] = '\0';
			append_to_buffer(phrase, increase);
			hasEnlarged = 1;
		}
		break;
	}
	if (hasEnlarged)
	{
		free(info->prompt_user);
		info->prompt_user = _strclone(phrase);
	}
}

/**
 * append_to_buffer - the function adds a string to the buffer at the end
 * @cache: this represents the buffer
 * @joinStrings: represents what the buffer will copy
 * Return: handle errno appropriately, and returns void
 */
int append_to_buffer(char *cache, char *joinStrings)
{
	int textLength, m;

	textLength = _strlen(cache);
	for (m = 0; joinStrings[m]; m++)
	{
		cache[textLength + m] = joinStrings[m];
	}
	cache[textLength + m] = '\0';
	return (textLength + m);
}
