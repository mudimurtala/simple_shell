#include "mutaShell.h"
/**
 * main - The main entry for any C program
 * @argc: stores the number of args received
 * @argv: stores the string received from the user
 * @env: denotes environment variables
 * Return:(0) at success
 */

int main(int argc, char *argv[], char *env[])
{
	d_of mt_struct = {NULL}, *mt = &mt_struct;
	char *om = "";

	bial_d(mt, argc, argv, env);

	signal(SIGINT, answer_z);


	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		om = SHOW;
	}

	errno = 0;
	sisifo(om, mt);
	return (0);
}
