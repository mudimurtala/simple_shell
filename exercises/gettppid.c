#include <stdio.h>
#include <unistd.h>

int main(void)
{

	pid_t ppid, pid;

pid = getpid();
	ppid = getppid();
	printf("Ppid %u\n Pid = %u\n", ppid, pid);

}
