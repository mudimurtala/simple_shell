#include "main.h"
#define MAX_ARGS 30

int main(void)
{
	char *args[MAX_ARGS + 2];
	char* buff = NULL;
	size_t len = 0;
	int status;

	printf("$ ");

	while (getline(&buff, &len, stdin) != -1)
	{
/*		int length = strlen(buff);
		buff[length - 1] = '\0';

*/		int count = 0;
		char *token = strtok(buff, " \n");
		while (token != NULL)
		{
			args[count] = token;
			count++;
			token = strtok(NULL, " \n");
		}

		args[count] = NULL;
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
//char *envp[] = {NULL};
			if (execvp(args[0], args) == -1);
			{
				perror("execve");
				exit(1);
			}
		}
		else
		{
			wait(&status);
		}
		printf("$ ");
	}
	printf("/n");
	return 0;
}
