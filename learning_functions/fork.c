#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

//Basic fork() exemple.
// int	main(void)
// {

// 	fork();
// 	printf("Hello world\n");
// 	return (0);
// }

int	main(void)
{
	int	id1;
	int	id2;

	id1 = fork();
	id2 = fork();
	if (id1 == 0)
	{
		if (id2 == 0)
			printf("Process <y>\n");
		else
			printf("Process <x>\n");
	}
	else
	{
		if (id2 == 0)
			printf("Process <z>\n");
		else
			printf("Process <original>\n");
	}
	while (wait(NULL) != -1 || errno != ECHILD)
	{
		printf("Waiting for child process to terminate\n");
	}
	return (0);
}
