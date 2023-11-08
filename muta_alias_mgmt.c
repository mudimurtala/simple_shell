#include "mutashell.h"

/**
 * mtalias_printing - add, remove or show aliases
 * @mtdata: struct for the program's data
 * @mtalias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int mtalias_printing(mt_program_data *mtdata, char *mtalias)
{
	int ind, ind2, mtalias_len;
	char buff[250] = {'\0'};

	if (mtdata->mt_list_alias)
	{
		mtalias_len = mutaStrlen(mtalias);
		for (ind = 0; mtdata->mt_list_alias[ind]; ind++)
		{
			if (!mtalias || (mutaStrcomp(mtdata->mt_list_alias[ind], mtalias, mtalias_len)
						&&	mtdata->mt_list_alias[ind][mtalias_len] == '='))
			{
				for (ind2 = 0; mtdata->mt_list_alias[ind][ind2]; ind2++)
				{
					buff[ind2] = mtdata->mt_list_alias[ind][ind2];
					if (mtdata->mt_list_alias[ind][ind2] == '=')
						break;
				}
				buff[ind2 + 1] = '\0';
				mutaBuff_add(buff, "'");
				mutaBuff_add(buff, mtdata->mt_list_alias[ind] + ind2 + 1);
				mutaBuff_add(buff, "'\n");
				_output(buff);
			}
		}
	}

	return (0);
}

/**
 * find_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *find_alias(mt_program_data *mtdata, char *alias_name)
{
	int ind, alias_len;

	/* validate the arguments */
	if (alias_name == NULL)
		return (NULL);
	if (mtdata->mt_list_alias == NULL)
		return (NULL);

	alias_len = mutaStrlen(alias_name);

	for (ind = 0; mtdata->mt_list_alias[ind]; ind++)
	{/* Iterates through the environ and check for coincidence of the varname */
		if (mutaStrcomp(alias_name, mtdata->mt_list_alias[ind], alias_len) &&
				mtdata->mt_list_alias[ind][alias_len] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (mtdata->mt_list_alias[ind] + alias_len + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * position_alias - function to update or overwrite alias
 * @mtalias_str: alias to be positioned
 * @mtdata: structure of the program's data
 * Return: 0 on sucess, otherwise any number declared in the argument
 */
int position_alias(char *mtalias_str, mt_program_data *mtdata)
{
	int ind, ind1;
	char buff[250] = {'0'}, *temp0 = NULL;

	/* validate the arguments */
	if (mtalias_str == NULL ||  mtdata->mt_list_alias == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (ind = 0; mtalias_str[ind]; ind++)
		if (mtalias_str[ind] != '=')
			buff[ind] = mtalias_str[ind];
		else
		{/* search if the value of the alias is another alias */
			temp0 = find_alias(mtdata, mtalias_str + ind + 1);
			break;
		}

	/* Iterates through the alias list and check for coincidence of the varname */
	for (ind1 = 0; mtdata->mt_list_alias[ind1]; ind1++)
		if (mutaStrcomp(buff, mtdata->mt_list_alias[ind1], ind) &&
				mtdata->mt_list_alias[ind1][ind] == '=')
		{/* if the alias alredy exist */
			free(mtdata->mt_list_alias[ind1]);
			break;
		}

	/* add the alias */
	if (temp0)
	{/* if the alias already exist */
		buff_add(buff, "=");
		buff_add(buff, temp0);
		mtdata->mt_list_alias[ind1] = mutaStrclone(buff);
	}
	else /* if the alias does not exist */
		mtdata->mt_list_alias[ind1] = mutaStrclone(mtalias_str);
	return (0);
}
