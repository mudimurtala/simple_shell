#include "mutashell.h"

int validate_file(char *absolute_file_path);

/**
 * locate_prog - search the PATH environment variable for a program
 * @info: this points to the data or info stored
 * Return: error code if error is encountered, (0) if successful
 */

int locate_prog(mt_code_info *info)
{
	int m = 0, outcome_status = 0;
	char **dirCollections;

	if (!info->command_tag)
		return (2);

	/** check whether it is an executable or has it's own full path */
	if (info->command_tag[0] == '/' || info->command_tag[0] == '.')
		return (validate_file(info->command_tag));

	free(info->passed_items[0]);
	info->passed_items[0] = _strlink(_strclone("/"), info->command_tag);
	if (!info->passed_items[0])
		return (2);

	dirCollections = breakdownPath(info);/* look for it in the PATH environment */

	if (!dirCollections || !dirCollections[0])
	{
		errno = 127;
		return (127);
	}
	for (m = 0; dirCollections[m]; m++)
	{/* join the name of the function to the PATH */
		dirCollections[m] = _strlink(dirCollections[m], info->passed_items[0]);
		outcome_status = validate_file(dirCollections[m]);
		if (outcome_status == 0 || outcome_status == 126)
		{
		/* the file was found, is not a directory and has execute permisions*/
			errno = 0;
			free(info->passed_items[0]);
			info->passed_items[0] = _strclone(dirCollections[m]);
			cleanup_pointer_array(dirCollections);
			return (outcome_status);
		}
	}
	free(info->passed_items[0]);
	info->passed_items[0] = NULL;
	cleanup_pointer_array(dirCollections);
	return (outcome_status);
}

/**
 * breakdownPath - split or tokenize the path in directories
 * @info: points to the data stored 
 * Return: it returns an array
 */

char **breakdownPath(mt_code_info *info)
{
	int m = 0;
	int dirCount = 2;
	char **passed_items = NULL;
	char *PATH;

	/* obtaining the value of the PATH variable */
	PATH = obtain_environment_secret("PATH", info);
	if ((PATH == NULL) || PATH[0] == '\0')
	{/*if the value is not found in the PATH*/
		return (NULL);
	}

	PATH = _strclone(PATH);

	/* check the PATH variable to know the numberof dirs */
	for (m = 0; PATH[m]; m++)
	{
		if (PATH[m] == ':')
			dirCount++;
	}

	/* array of pointers should be reserved a space  */
	passed_items = malloc(sizeof(char *) * dirCount);

	/*duplicate, split and tokenize the parts of the PATH*/
	m = 0;
	passed_items[m] = _strclone(_strsplit(PATH, ":"));
	while (passed_items[m++])
	{
		passed_items[m] = _strclone(_strsplit(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (passed_items);

}

/**
 * validate_file - a function tasked with checking whether a file exists
 * and validating its executing permisions
 * @absolute_file_path: the represent the variable pointing to the file
 * Return: an error code, but (0) if successful
 */

int validate_file(char *absolute_file_path)
{
	struct stat sb;

	if (stat(absolute_file_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(absolute_file_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*if the file is not in existence*/
	errno = 127;
	return (127);
}
