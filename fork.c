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


//Basic wait() exemple.
// int	main(void)
// {
// 	int	pid;
// 	int	i;
// 	int	n;

// 	i = 0;
// 	pid = fork();
// 	if (pid == 0)
// 		n = 1;
// 	else
// 		n = 6;
// 	if (pid != 0)
// 		wait(NULL);
// 	else
// 		printf("\n");
// 	for (i = n; i < n + 5; i++)
// 	{
// 		printf("%d ", i);
// 		fflush(stdout);
// 	}

// 	return (0);
// }

//wait() used for condition

// int	main(void)
// {
// 	int	wait_result;
// 	fork();
// 	wait_result = wait(NULL);
// 	if (wait_result == -1)
// 		printf("The process %d dont have any children process\n", getppid());
// 	else
// 		printf("The child process %d have terminate is process\n", wait_result);
// 	return (0);
// }

//Basic getpid() exemple.
// int	main(void)
// {
// 	fork();
// 	printf("%d\n", getpid());
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
