#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

//Basic fork() exemple.
int	main(void)
{

	fork();
	printf("Hello world\n");
	return (0);
}

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

// Fork exercise 1, basic fork
int	basic_fork(void)
{
	int	id;

	id = fork();
	if (id == -1)
	{
		printf("Fork probleme\n");
		return (1);
	}
	if (id == 0)
		printf("Print form the child process\n");
	else
		printf("Print form the parent process\n");
	return (0);
}

// Fork exercise 1, Integrate the wait function to wait for child process to finish!
int	basic_fork_with_wait(void)
{
	int	id;

	id = fork();
	if (id == -1)
	{
		printf("Fork probleme\n");
		return (1);
	}
	if (id == 0)
		printf("Print form the child process\n");
	else
	{
		wait(NULL);
		printf("Print form the parent process\n");
	}
	return (0);
}

// Fork exercise 1, a fork from a child process
int	basic_fork_into_a_fork(void)
{
	int	id;
	int	id2;

	id = fork();
	if (id == -1)
	{
		printf("Fork probleme\n");
		return (1);
	}
	if (id == 0)
	{
		printf("Print form the child process\n");
		id2 = fork();
		if (id2 == -1)
		{
			printf("Fork probleme!\n");
			return (-1);
		}
		if (id2 == 0)
			printf("Print form the second child process\n");
		else
		{
			wait(NULL);
			printf("Print form the second parent process\n");
		}
	}
	else
	{
		wait(NULL);
		printf("Print form the parent process\n");
	}
	return (0);
}

int	main(void)
{
	basic_fork_into_a_fork();
	return (0);
}
