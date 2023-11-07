#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	int i;

	for (i = 0; i < 5; i++) 
	{
		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			char *args[] = {"/bin/ls", "-l", "/tmp", NULL};
			if (execve("/bin/ls", args, NULL) == -1)
			{
				perror("execve");
				exit(1);
			}
		}
		else
		{
			int status;
			if (wait(&status) == -1)
			{
				perror("wait");
				exit(1);
			}
		}
	}

	return 0;
}
