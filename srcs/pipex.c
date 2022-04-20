/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:43:11 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/19 21:39:33 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

static char	*path_env_var_to_str(char **p_envp)
{
	int		i;

	i = 0;
	if (p_envp)
	{
		while (p_envp[i] != NULL)
		{
			if (strncmp(p_envp[i], "PATH=", 5) == 0)
			{
				//ft_printf("%s\n", p_envp[i]);
				return (ft_strtrim(p_envp[i], "PATH="));
			}
			i++;
		}
	}
	return (NULL);
}

char	*recup_the_bin_path(char *bin_name, char **p_envp)
{
	char	**splitted_path;
	char	*trimmed_path;
	char	*complete_bin_path;
	int		i;

	i = 0;
	complete_bin_path = NULL;
	trimmed_path = path_env_var_to_str(p_envp);
	splitted_path = ft_split(trimmed_path, ':');
	free(trimmed_path);
	while (splitted_path[i])
	{
		complete_bin_path = ft_strjoin(splitted_path[i], "/");
		complete_bin_path = ft_strjoin(complete_bin_path, bin_name);
		if (access(complete_bin_path, X_OK) != -1)
		{
			clear_char_tab(splitted_path);
			return (complete_bin_path);
		}
		i++;
	}
	free (complete_bin_path);
	clear_char_tab(splitted_path);
	return (NULL);
}

static int	execution(char *p_argv, char **p_envp)
{
	char	**cmd;
	char	*absolute_path;

	cmd = ft_split(p_argv, ' ');
	absolute_path = recup_the_bin_path(cmd[0], p_envp);
	ft_printf("absolute path = %s \n", absolute_path);
	if (execve(absolute_path, cmd, p_envp) == -1)
	{
		clear_char_tab(cmd);
		free(absolute_path);
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	outfile_fdnum;
	int	i;
	int	fork_pid;
	int	pipefd[2];

	outfile_fdnum = 0;

	// If outfile not exist, open with O_CREAT flag
	outfile_fdnum = open(argv[(argc - 1)], O_WRONLY);
	if (outfile_fdnum == -1)
		outfile_fdnum = open(argv[(argc - 1)], O_CREAT, S_IWUSR | S_IWGRP | S_IWOTH);
	i = 2;
	while (i < (argc - 1))
	{
		fork_pid = fork();
		if (fork_pid == 0)
		{
			if (execution(argv[i], envp) == -1)
				return (ft_printf("Exec probleme\n"));
		}
		else if (fork_pid != 0)
			wait(0);
		i++;
	}
	return (ft_printf("return from parent\n"));
}
