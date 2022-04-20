/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:43:11 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/20 12:39:25 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

// static char	*path_env_var_to_str(char **p_envp)
// {
// 	int		i;

// 	i = 0;
// 	if (p_envp)
// 	{
// 		while (p_envp[i] != NULL)
// 		{
// 			if (strncmp(p_envp[i], "PATH=", 5) == 0)
// 			{
// 				//ft_printf("%s\n", p_envp[i]);
// 				return (ft_strtrim(p_envp[i], "PATH="));
// 			}
// 			i++;
// 		}
// 	}
// 	return (NULL);
// }

// char	*recup_the_bin_path(char *bin_name, char **p_envp)
// {
// 	char	**splitted_path;
// 	char	*trimmed_path;
// 	char	*complete_bin_path;
// 	int		i;

// 	i = 0;
// 	complete_bin_path = NULL;
// 	trimmed_path = path_env_var_to_str(p_envp);
// 	splitted_path = ft_split(trimmed_path, ':');
// 	free(trimmed_path);
// 	while (splitted_path[i])
// 	{
// 		complete_bin_path = ft_strjoin(splitted_path[i], "/");
// 		complete_bin_path = ft_strjoin(complete_bin_path, bin_name);
// 		if (access(complete_bin_path, X_OK) != -1)
// 		{
// 			clear_char_tab(splitted_path);
// 			return (complete_bin_path);
// 		}
// 		i++;
// 	}
// 	free (complete_bin_path);
// 	clear_char_tab(splitted_path);
// 	return (NULL);
// }

// static int	execution(char *p_argv, char **p_envp)
// {
// 	char	**cmd;
// 	char	*absolute_path;

// 	cmd = ft_split(p_argv, ' ');
// 	absolute_path = recup_the_bin_path(cmd[0], p_envp);
// 	ft_printf("absolute path = %s \n", absolute_path);
// 	if (execve(absolute_path, cmd, p_envp) == -1)
// 	{
// 		clear_char_tab(cmd);
// 		free(absolute_path);
// 		return (-1);
// 	}
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	(void) envp;
	int	outfile_fdnum;
	int	i;
	int	j;
	int	fork_pid[argc - 3];
	int	waitpid_status;
	//int	pipefd[2]; //fd[0] = read  //fd[1] = write

	outfile_fdnum = 0;

	// If outfile not exist, open with O_CREAT flag
	outfile_fdnum = open(argv[(argc - 1)], O_WRONLY);
	if (outfile_fdnum == -1)
		outfile_fdnum = open(argv[(argc - 1)], O_CREAT, S_IWUSR | S_IWGRP | S_IWOTH);
	i = 0;
	while (i < (argc - 4))
	{
		fork_pid[i] = fork();

		if (fork_pid[i] != 0)
		{
			ft_printf("Parent fork_pid = %d\n", fork_pid[i]);
			ft_printf("Parent process i = %d\n", i);
		}
		i++;
	}
	j = 0;
	while (j < (argc - 3))
	{
		if (fork_pid[j] == 0)
		{
			ft_printf("Child fork_pid = %d\n", fork_pid[j]);
			ft_printf("Child process i = %d\n", j);
		}
		else if (fork_pid[j] != 0)
			waitpid(fork_pid[j], &waitpid_status, 0);
		j++;
	}
	// i = 0;
	// while (i < (argc - 1))
	// {
	// 	if (fork_pid[i] == 0)
	// 	{
	// 		if (execution(argv[i], envp) == -1)
	// 			return (ft_printf("Exec probleme\n"));
	// 	}
	// 	else if (fork_pid[i] != 0)
	// 		wait(0);
	// 	i++;
	// }
	return (ft_printf("return from parent\n"));
}
