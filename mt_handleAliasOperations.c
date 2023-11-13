#include "mutashell.h"

/**
 * mt_manageAlias - function to insert, delete or print aliases
 * @info: struct for the program's info
 * @alias_name: name of the alias to be displayed
 * Return: 0 upon success, otherwise user declared number
 */
int mt_manageAlias(mt_code_info *info, char *alias_name)
{
	int ind, ind2, mtalias_len;
	char buff[250] = {'\0'};

	if (info->mt_listAlias)
	{
		mtalias_len = _strlen(alias_name);
		for (ind = 0; info->mt_listAlias[ind]; ind++)
		{
			if (!alias_name || (_strcomp(info->mt_listAlias[ind], alias_name,
			mtalias_len) && info->mt_listAlias[ind][mtalias_len] == '='))
			{
				for (ind2 = 0; info->mt_listAlias[ind][ind2]; ind2++)
				{
					buff[ind2] = info->mt_listAlias[ind][ind2];
					if (info->mt_listAlias[ind][ind2] == '=')
						break;
				}
				buff[ind2 + 1] = '\0';
				append_to_buffer(buff, "'");
				append_to_buffer(buff, info->mt_listAlias[ind] + ind2 + 1);
				append_to_buffer(buff, "'\n");
				_display(buff);
			}
		}
	}

	return (0);
}

/**
 * mt_findAlias - add, remove or show aliases
 * @info: struct for the program's data
 * @alias_name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *mt_findAlias(mt_code_info *info, char *alias_name)
{
	int ind, alias_len;

	/* validate the arguments */
	if (alias_name == NULL)
{
		return (NULL);
}
	if (info->mt_listAlias == NULL)
{
		return (NULL);
}
	alias_len = _strlen(alias_name);

	for (ind = 0; info->mt_listAlias[ind]; ind++)
	{/* Iterates through the environ and check for coincidence of the varname */
		if (_strcomp(alias_name, info->mt_listAlias[ind], alias_len) &&
				info->mt_listAlias[ind][alias_len] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (info->mt_listAlias[ind] + alias_len + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * mt_positionAlias - function to update or overwrite alias
 * @mtalias_str: alias to be positioned
 * @info: structure of the program's data
 * Return: 0 on success, otherwise any number declared in the argument
 */
int mt_positionAlias(char *mtalias_str, mt_code_info *info)
{
	int ind, ind1;
	char buff[250] = {'0'}, *var = NULL;

	/* validate the arguments */
	if (mtalias_str == NULL ||  info->mt_listAlias == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (ind = 0; mtalias_str[ind]; ind++)
		if (mtalias_str[ind] != '=')
			buff[ind] = mtalias_str[ind];
		else
		{/* search if the value of the alias is another alias */
			var = mt_findAlias(info, mtalias_str + ind + 1);
			break;
		}

	/* Iterates through the alias list and check for coincidence of the varname */
	for (ind1 = 0; info->mt_listAlias[ind1]; ind1++)
		if (_strcomp(buff, info->mt_listAlias[ind1], ind) &&
				info->mt_listAlias[ind1][ind] == '=')
		{/* if the alias alredy exist */
			free(info->mt_listAlias[ind1]);
			break;
		}

	/* add the alias */
	if (var)
	{/* if the alias already exist */
		append_to_buffer(buff, "=");
		append_to_buffer(buff, var);
		info->mt_listAlias[ind1] = _strclone(buff);
	}
	else /* if the alias does not exist */
		info->mt_listAlias[ind1] = _strclone(mtalias_str);
	return (0);
}
