/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:19:28 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/09 14:51:50 by tchalifo         ###   ########.fr       */
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

static char	*recup_the_bin_path(char *bin_name, char **p_envp)
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

int	cmd_parsing(t_cmdinfos_data *exec_data, char *p_argv, char **envp)
{
	exec_data->cmd_argument = ft_split(p_argv, ' ');
	exec_data->absolute_path = recup_the_bin_path(exec_data->cmd_argument[0], envp);
	return (0);
}

void	setup_input(t_data *prog_data)
{
	/* 1. si premiere iteration, dup2 le stdin 0 avec le filesfd[0]
	else, dup2 le stdin 0 avec le pipefd[0] READEND.
	*/
	if (prog_data->mainloop_i == 2) // Premiere execution
	{
		dprintf(2, "La premiere execution TEST READ\n");
		dup2(prog_data->filesfd[0], 0);
		close(prog_data->filesfd[0]);
	}
	else
	{
		dprintf(2, "Les autres execution TEST READ\n");
		close(prog_data->pipefd[WRITE_ENDPIPE]);
		dup2(prog_data->pipefd[READ_ENDPIPE], 0);
		close(prog_data->pipefd[READ_ENDPIPE]);
	}
}
void	setup_output(t_data *prog_data, int argc)
{
	/* 2. si derniere iteration, dup2 le stdout 1 avec le filesfd[1]
	else, dup2 le stdout 1 avec le pipefd[1] WRITEEND.
	*/

	if (prog_data->mainloop_i == argc - 2) // Derniere execution
	{
		dprintf(2, "Derniere execution TEST WRITE\n");
		dup2(prog_data->filesfd[1], 1);
		close(prog_data->filesfd[1]);
	}
	else
	{
		dprintf(2, "Les premieres executions TEST WRITE\n");
		close(prog_data->pipefd[READ_ENDPIPE]);
		dup2(prog_data->pipefd[WRITE_ENDPIPE], 1);
		close(prog_data->pipefd[WRITE_ENDPIPE]);
	}
}

int	execution_time(t_cmdinfos_data *exec_data, char **envp)
{
	if (execve(exec_data->absolute_path, exec_data->cmd_argument, envp) == -1)
	{
		clear_char_tab(exec_data->cmd_argument);
		free(exec_data->absolute_path);
		dprintf(2, "Execution probleme\n");
		return (-1);
	}
	return (0);
}
