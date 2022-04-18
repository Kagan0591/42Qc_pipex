/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 09:27:40 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/18 13:31:27 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	execution(char *p_argv, char **p_envp)
{
	char **cmd;

	cmd = ft_split(p_argv, ' ');
	// char	*exec_vector[] = {cmd[0], cmd[1], cmd[2], NULL};
	// printf("argv = %s\n", p_argv);
	//printf("exec_vector[0] = %s\n", exec_vector[0]);
	if (execve("/bin/echo", cmd, p_envp) == -1)
	{
		clear_char_tab(cmd, ft_strlen(*cmd));
		return (-1);
	}
	clear_char_tab(cmd, ft_strlen(*cmd));
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
	(void)	argc;
	int		pipe_fd[2];
	int		fd;
	int		pid;
	char	*bin_path;
	char	**bin_n_option;
	int		i;
	d_exec *cmd_args;

	//ARGS count check (ONLY MANDATORIE)
	if (argc != 5)
	{
		ft_printf("Args count probleme\n");
		return (1);
	}

	// Check if outfile is already created, if not create it


	// split the execs arguments, placing name and options separatly into a tab
	i = 2;
	while (i < argc)
	{
		bin_n_option = ft_split(argv[i], ' ');
		if (fill_in_exec_struct(bin_n_option[0], cmd_args, envp) == -1)
			return (2);
		i++;
	}

	if (pipe_init(pipe_fd) == -1) // pipe_fd[0] == read pipe_fd[1] == Write
		return (3);

	while (argc > 3)
	{
		pid = fork();
		if (pid == 0)
		{
			//child process
			ft_printf("Child process scope\n");
			close(pipe_fd[0]);
			if (execution(argv[2], envp) == -1)
				return (4);
			ft_printf("Child scope end\n");
		}
		else
		{
			//parent process
			waitpid(0, NULL, 0);
			ft_printf("Parent process scope\n");
			if (execution(argv[3], envp) == -1)
				return (5);
			fd = open("outfile", O_CREAT);
			ft_printf("%d\n", fd);
			ft_printf("Parent scope end\n");
		}
	}
	return (0);
}
