#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

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