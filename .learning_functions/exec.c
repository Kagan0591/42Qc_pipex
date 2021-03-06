#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int	demo_execl()
{
	execl("/bin/ls", "ls", "../", NULL);
	return (0);
}


int	demo_execlp()
{
	execlp("ls", "ls", "../learning_functions", NULL);
	return (0);
}

int	demo_execvp()
{
	char *exec_vector[] = { "ls", "../", NULL };
	execvp("ls", exec_vector);
	return (0);
}

int	demo_execle(char **p_envp)
{
	execle("/bin/echo", "echo", "Hello", "World", NULL, p_envp);
	int err = errno;
	printf("Error code: %d\n", err);
	return (0);
}

int	demo_execve(char **p_envp)
{
	char *exec_vector[] = {"/bin/echo", "Hello", "World", NULL};
	execve("/bin/echo", exec_vector, p_envp);
	int err = errno;
	printf("Error code: %d\n", err);
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	(void) argc;
	(void) argv;

	// (void) envp;
	//demo_execl();
	//demo_execvp();
	demo_execve(envp);
	printf("programme have finish to execute\n");
	return (0);
}