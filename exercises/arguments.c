#include <stdio.h>

int main(int ac, char **av)
{
(void) ac;
	int index;
	for (index = 0; av[index] != NULL; index++)
	{
		printf("%s \n", av[index]);
	}

	return 0;
}
