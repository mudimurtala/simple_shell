#include "main.h"

int main(int *ac, char **av)
{

	char *buff;
	size_t addr;

	printf("$ ");


	buff = (char *)malloc(addr * sizeof(char));
	if (buff == NULL)
	{
		perror("ERROR!");
		exit(1);
	}


	while (getline(&buff, &addr, stdin) != 	EOF)
	{
		printf("%s\n", buff);
		printf("$ ");
	}

	free(buff);
	return 0;
}
