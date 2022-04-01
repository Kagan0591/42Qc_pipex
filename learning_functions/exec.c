#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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

int	demo_execve(char *p_envp[])
{
	(void) p_envp;
	char *exec_vector[] = { "bin/ping", "../", NULL };
	char *env[] = {"TEST=environnment variable", NULL};
	execve("bin/ping", exec_vector, env);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	//demo_execl();
	demo_execve(envp);
	printf("programme have finish to execute\n");
	return (0);
}
