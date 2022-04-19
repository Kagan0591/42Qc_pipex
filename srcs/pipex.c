/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:43:11 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/18 21:14:51 by tchalifo         ###   ########.fr       */
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
	while (splitted_path[i])
	{
	#error Verifier la splitted_path variable
		complete_bin_path = ft_strjoin(splitted_path[i], bin_name);
		//ft_printf("splitted path : %s\n", splitted_path[i]);
		if (access(complete_bin_path, X_OK) != -1)
		{
			clear_char_tab(splitted_path);
			free (complete_bin_path);
			complete_bin_path = NULL;
			return (complete_bin_path);
		}
		i++;
	}
	clear_char_tab(splitted_path);
	free(trimmed_path);
	return (NULL);
}

static int	execution(char *p_argv, char **p_envp)
{
	char	**cmd;
	char	*absolute_path;

	absolute_path = recup_the_bin_path(p_argv, p_envp);
	cmd = ft_split(p_argv, ' ');
	ft_printf("%s\n", absolute_path);
	if (execve(absolute_path, cmd, p_envp) == -1)
	{
		ft_printf("TEST\n");
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

	outfile_fdnum = 0;

	// If outfile not exist, open with O_CREAT flag
	outfile_fdnum = open(argv[(argc - 1)], O_WRONLY);
	if (outfile_fdnum == -1)
		outfile_fdnum = open(argv[(argc - 1)], O_CREAT, S_IWUSR | S_IWGRP | S_IWOTH);
	i = 2;
	ft_printf("%d\n",argc);
	while (i < argc)
	{
		fork_pid = fork();
		if (fork_pid == 0)
		{
			if (execution(argv[i], envp) == -1)
				return (1);
		}
		else if (fork_pid != 0)
			wait(0);
		i++;
	}
	return (ft_printf("return from parent\n"));
}