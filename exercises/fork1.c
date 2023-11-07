#include <stdio.h>
#include <unistd.h>

int main()
{
pid_t p = fork();
	printf("Alx is fun from %d\n", p);
	return 0;
}
