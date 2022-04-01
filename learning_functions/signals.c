#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

int	main(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("Fork probleme!\n");
		return(1);
	}
	if (pid == 0)
	{
		while (1)
		{
			printf("repeated string\n");
			usleep(500000);
		}
	}
	else
	{
		sleep(2);
		kill(pid, SIGKILL);
		wait(NULL);
	}
	return (0);
}