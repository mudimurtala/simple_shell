#include "mutashell.h"

/**
 * obtain_environment_secret - obtain what is inside an environment variable
 * @secret: represent the environment value
 * @info: represents the data of the program
 * Return: it returns a pointer
 */
char *obtain_environment_secret(char *secret, mt_code_info *info)
{
	int m, secret_length = 0;

	/* prove the parameters or arguments */
	if (secret == NULL || info->environ == NULL)
		return (NULL);

	/* getting the length of the variable in question */
	secret_length = _strlen(secret);

	for (m = 0; info->environ[m]; m++)
	{/* create a loop inside of the environ */
		if (_strcomp(secret, info->environ[m], secret_length) &&
		 info->environ[m][secret_length] == '=')
		{/* returns the value of the key NAME=  when find it*/
			return (info->environ[m] + secret_length + 1);
		}
	}
	/* NULL is returned if not found*/
	return (NULL);
}

/**
 * config_environment_secret - write over the value that an environment holds,
 * or another one created if not exist.
 * @secret: represents the new variable
 * @element: another value 
 * @info: represents the data the program stores
 * Return: (0) for success, 1 for NULL and 2 for error
 */

int config_environment_secret(char *secret, char *element, mt_code_info *info)
{
	int m, secret_length = 0, keyChanged = 1;

	/* proof if the argument's are true or false */
	if (secret == NULL || element == NULL || info->environ == NULL)
		return (1);

	/* getting the length of the variable in confidenve */
	secret_length = _strlen(secret);

	for (m = 0; info->environ[m]; m++)
	{/* looping the environ */
		if (_strcomp(secret, info->environ[m], secret_length) &&
		 info->environ[m][secret_length] == '=')
		{
		/* If there is secret in existence */
			keyChanged = 0;
			/* the variable is now being freed */
			free(info->environ[m]);
			break;
		}
	}
	/* a string if this form "secret=element" is created */
	info->environ[m] = _strlink(_strclone(secret), "=");
	info->environ[m] = _strlink(info->environ[m], element);

	if (keyChanged)
	{
	/* if the variable is new, it is create at end of actual list and we need*/
	/* to put the NULL value in the next position */
		info->environ[m + 1] = NULL;
	}
	return (0);
}

/**
 * clear_environment_secret - clear the created "secret" from the env variable
 * @secret: represent what is to be removed
 * @info: represents the data that the program stores
 * Return: (0) if it does not exist and (1) if already removed
 */
int clear_environment_secret(char *secret, mt_code_info *info)
{
	int m, secret_length = 0;

	/* proof whether the arguments are true */
	                                                                                                                                                                                                                                                                                                                             if (secret == NULL || info->environ == NULL)
		return (0);

	/* grtting the length of the needed variable */
	secret_length = _strlen(secret);

	for (m = 0; info->environ[m]; m++)
	{/* looping through the environment variable */
		if (_strcomp(secret, info->environ[m], secret_length) &&
		 info->environ[m][secret_length] == '=')
		{/* remove the "secret" if already exist */
			free(info->environ[m]);

			/* 'secrets' ar moved downward just a single position */
			m++;
			for (; info->environ[m]; m++)
			{
				info->environ[m - 1] = info->environ[m];
			}
			/* the end list should be assigned a NULL */
			info->environ[m - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * display_environment - display the present environment
 * @info: represents the data the program stores
 * Return: returns a void
 */
void disply_environment(mt_code_info *info)
{
	int n;

	for (n = 0; info->environ[n]; n++)
	{
		_print(info->environ[n]);
		_print("\n");
	}
}
