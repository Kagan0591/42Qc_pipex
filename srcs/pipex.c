/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 09:27:40 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/13 09:27:45 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	execution(char *p_argv, char **p_envp)
{
	char	*exec_vector[] = {p_argv, "Hello", "World", NULL};
	printf("argv = %s\n", p_argv);
	printf("exec_vector[0] = %s\n", exec_vector[0]);
	if (execve("/bin/echo", exec_vector, p_envp) == -1)
		return (-1);
	return (0);
}

static int	pipe_init(int *p_fd)
{
	if (pipe(p_fd) == -1)
	{
		ft_printf("Pipe initialisation probleme\n");
		return(-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	int	fd[2];
	int	pid;

	if (pipe_init(fd) == -1)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		//child process
		ft_printf("Child process scope\n");
		execution(argv[1], envp);
		ft_printf("Child scope end\n");
	}
	else
	{
		//parent process
		waitpid(0, NULL, 0);
		ft_printf("Parent process scope\n");

		ft_printf("Parent scope end\n");

	}
	return (0);
}
