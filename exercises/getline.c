#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *buff = NULL;
	size_t count = 0;
	char *prompt = "$ ";

	printf("%s", prompt);
	while (getline(&buff, &count, stdin) != EOF)
	{
		printf("%s\n", buff);
		printf("%s", prompt);
	}

	printf("\n");
	free(buff);
	return 0;
}
