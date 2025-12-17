#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	pid_t parent_pid;
	parent_pid = getppid();
	printf("%d\n", parent_pid);
	return (0);
}