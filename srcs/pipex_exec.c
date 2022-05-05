/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:19:28 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/05 15:57:55 by tchalifo         ###   ########.fr       */
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
	//dprintf(2, "absolute path = %s\n", absolute_path);
	if (execve(absolute_path, cmd, envp) == -1)
	{
		clear_char_tab(cmd);
		free(absolute_path);
		//dprintf(2, "Execution probleme\n");
		return (-1);
	}
	return (0);
}

void	setup_io(t_data *prog_data, int argc)
{
	//input
	if (prog_data->mainloop_i == 2) // Premiere execution
	{
		//dprintf(2, "La premiere execution TEST READ\n");
		dup2(prog_data->filesfd[0], 0);
		close(prog_data->filesfd[0]);
	}
	else
	{
		//dprintf(2, "Les autres execution TEST READ\n");
		close(prog_data->pipefd[WRITE_ENDPIPE]);
		dup2(prog_data->pipefd[READ_ENDPIPE], 0);
		close(prog_data->pipefd[READ_ENDPIPE]);
	}
	//output
	if (prog_data->mainloop_i == argc - 2) // Derniere execution
	{
		//dprintf(2, "Derniere execution TEST WRITE\n");
		dup2(prog_data->filesfd[1], 1);
		close(prog_data->filesfd[1]);

	}
	else
	{
		//dprintf(2, "Les premieres executions TEST WRITE\n");
		close(prog_data->pipefd[READ_ENDPIPE]);
		dup2(prog_data->pipefd[WRITE_ENDPIPE], 1);
		close(prog_data->pipefd[WRITE_ENDPIPE]);
	}
}
