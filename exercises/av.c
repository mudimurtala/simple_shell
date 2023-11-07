#include "main.h"

int main(int *ac, char **av)
{
	int i;
	for (i = 0; av[i] != NULL; i++)
	{
		printf("%s ", av[i]);
	}
	printf("\n");

	return 0;
}
