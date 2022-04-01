#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

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

//waitpid()

int	demo_waitpid(void)
{
	int	id;

	id = fork();
	if (id == -1)
	{
		printf("Fork probleme\n");
		return (1);
	}
	if (id == 0)
	{
		printf("Child process print HELLO!!!\n");
	}
	else
	{
		waitpid(id, NULL, 0);
		printf("Parent process print WORLD! :) \n");
	}
	return (0);
}

int	demo_wait_status(void)
{
	int	id;
	int exec_error;
	int	wait_status;
	int status_code;

	wait_status = 0;
	id = fork();
	if (id == -1)
	{
		printf("Fork probleme\n");
		return (1);
	}
	if (id == 0)
	{
		printf("this is the child process\n");
		exec_error = execl("/bin/ping", "bin/ping", "-c", "1", "google.con", NULL);
		if (exec_error == -1)
		{
			printf("Exec probleme\n");
			exit(1);
		}
	}
	else
	{
		wait(&wait_status);
		// wait_status &= 0xFF;
		wait_status &= 0xFF << 8;
		printf("This is the parent process: wait status  = %d\n", wait_status);
		if (WIFEXITED(wait_status))
		{
			status_code = WEXITSTATUS(wait_status);
			printf("The child process have terminated correctly with status code: %d\n", wait_status);
		}
		else
		{
			status_code = WEXITSTATUS(wait_status);
			printf("The child process have terminated correctly!\n");
		}
	}
	return (0);
}

int	main(void)
{
	//demo_waitpid();
	demo_wait_status();
	return (0);
}