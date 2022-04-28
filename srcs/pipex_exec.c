/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:19:28 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/27 20:17:59 by tchalifo         ###   ########.fr       */
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
				return (ft_strtrim(p_envp[i], "PATH="));
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

int	ft_execve(char *p_argv, char **envp)
{
	char	**cmd;
	char	*absolute_path;

	cmd = ft_split(p_argv, ' ');
	absolute_path = recup_the_bin_path(cmd[0], envp);
	dprintf(2, "absolute path = %s\n", absolute_path);
	int i = 0;
	while (i < ft_strlen(*cmd))
	{
		dprintf(2, "cmd tab into ft_execve = %s\n", cmd[i]);
		i++;
	}
	if (execve(absolute_path, cmd, envp) == -1)
	{
		clear_char_tab(cmd);
		free(absolute_path);
		dprintf(2, "Execution probleme\n");
		return (-1);
	}
	return (0);
}
//return the fd of outfile or
void	setupio(t_data *prg_data, int fork_pid, int argc)
{
/*
	1. si premiere iteration, dup2 le stdin 0 avec le filesfd[0]
	else, dup2 le stdin 0 avec le pipefd[0] READEND.
	2. si derniere iteration, dup2 le stdout 1 avec le filesfd[1]
	else, dup2 le stdout 1 avec le pipefd[1] WRITE.
*/
	if (fork_pid != 0) //Setup input
	{
		close(prg_data->pipefd[WRITE_ENDPIPE]);
		if (prg_data->mainloop_i == 2) // Premiere execution
			dup2(prg_data->filesfd[0], 0);
		else
			dup2(prg_data->pipefd[0], 0);
		close(prg_data->pipefd[0]);
	}
	else //Setup output
	{
		close(prg_data->pipefd[READ_ENDPIPE]);
		if (prg_data->mainloop_i == argc - 2) // Derniere execution
			dup2(prg_data->filesfd[1], 1);
		else
			dup2(prg_data->pipefd[1], 1);
		close(prg_data->pipefd[1]);
	}
}
