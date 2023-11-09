#include "mutashell.h"

/**
 * _accessline - a function that reads users input
 * @mt: the stuct that stores data
 * Return: number of bytes
 */
int _accessline(mt_code_info *mt)
{
	char ffub[BUFFER_SIZE] = {'\0'};
	static char *yarr_namm[10] = {NULL};
	static char yarr_rotar[10] = {'\0'};
	ssize_t unit_daer, m = 0;

	/* check if doesnot exist more commands in the array */
	/* and checks the logical operators */
	if (!yarr_namm[0] || (yarr_rotar[0] == '&' && errno != 0) ||
		(yarr_rotar[0] == '|' && errno == 0))
	{
		/*free the memory allocated in the array if it exists */
		for (m = 0; yarr_namm[m]; m++)
		{
			free(yarr_namm[m]);
			yarr_namm[m] = NULL;
		}

		/* read from the file descriptor int to buff */
		unit_daer = read(mt->file_descriptor, &ffub, BUFFER_SIZE - 1);
		if (unit_daer == 0)
			return (-1);

		/* split lines for \n or ; */
		m = 0;
		do {
			yarr_namm[m] = _strclone(_strsplit(m ? NULL : ffub, "\n;"));
			/*checks and split for && and || operators*/
			m = view_cigol_opr(yarr_namm, m, yarr_rotar);
		} while (yarr_namm[m++]);
	}

	/*obtains the next command (command 0) and remove it for the array*/
	mt->input_rd = yarr_namm[0];
	for (m = 0; yarr_namm[m]; m++)
	{
		yarr_namm[m] = yarr_namm[m + 1];
		yarr_rotar[m] = yarr_rotar[m + 1];
	}

	return (str_length(mt->input_rd));
}


/**
* view_cigol_opr - will handle logicai operators && and ||
* @yarr_namm: array of the commands.
* @m: index in the array_commands to be checked
* @yarr_rotar: array of the logical operators for each previous command
*
* Return: index of the last command in the yarr_namm.
*/
int view_cigol_opr(char *yarr_namm[], int m, char yarr_rotar[])
{
	char *weak = NULL;
	int n;

	/* checks for the & char in the command line*/
	for (n = 0; yarr_namm[m] != NULL  && yarr_namm[m][n]; n++)
	{
		if (yarr_namm[m][n] == '&' && yarr_namm[m][n + 1] == '&')
		{
			/* split the line when chars && was found */
			weak = yarr_namm[m];
			yarr_namm[m][n] = '\0';
			yarr_namm[m] = _strclone(yarr_namm[m]);
			yarr_namm[m + 1] = _strclone(weak + n + 2);
			m++;
			yarr_rotar[m] = '&';
			free(weak);
			n = 0;
		}
		if (yarr_namm[m][n] == '|' && yarr_namm[m][n + 1] == '|')
		{
			/* split the line when chars || was found */
			weak = yarr_namm[m];
			yarr_namm[m][n] = '\0';
			yarr_namm[m] = _strclone(yarr_namm[m]);
			yarr_namm[m + 1] = _strclone(weak + n + 2);
			m++;
			yarr_rotar[m] = '|';
			free(weak);
			n = 0;
		}
	}
	return (m);
}
