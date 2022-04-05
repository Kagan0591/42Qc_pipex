#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	int	fd[2];
	//int	pid;

	if (pipe(fd) == -1)
	{
		return (1);
	}
	ft_printf("\n");
	ft_putchar('n');
	return (0);
}
