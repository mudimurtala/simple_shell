#include "main.h"

int main(void)
{

	char *lineptr = NULL;
	size_t n = 0;
	ssize_t line;
	int len;

	printf("$ ");


	while (getline(&lineptr, &n, stdin) != EOF)
	{
		len = strlen(lineptr);
		lineptr[len - 1] = '\0';
		printf("%s, %u\n", lineptr, getpid());
		printf("$ ");
	}

printf("\n");

	exit(EXIT_SUCCESS);
}
