/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 10:19:28 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/18 13:56:17 by tchalifo         ###   ########.fr       */
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
		complete_bin_path = ft_strjoin_free_s1(complete_bin_path, bin_name);
		if (access(complete_bin_path, X_OK) != -1)
		{
			clear_char_tab(splitted_path);
			return (complete_bin_path);
		}
		i++;
	}
	clear_char_tab(splitted_path);
	free (complete_bin_path);
	perror(strerror(errno));
	exit(errno);
}

int	cmd_parsing(t_cmdinfos_data *exec_data, char *p_argv, char **envp)
{
	exec_data->cmd_argument = ft_split(p_argv, ' ');
	exec_data->absolute_path = \
		recup_the_bin_path(exec_data->cmd_argument[0], envp);
	return (0);
}

int	execution_time(t_data *prog_data, char **envp)
{
	while (prog_data->cmds_list != NULL)
	{
		setup_input(prog_data);
		if (pipe(prog_data->pipefd) == -1)
			perror(NULL);
		prog_data->cmds_list->var_data->fork_pid = fork();
		if (prog_data->cmds_list->var_data->fork_pid == -1)
			perror(NULL);
		else if (prog_data->cmds_list->var_data->fork_pid == 0)
		{
			setup_output(prog_data);
			if (execve(prog_data->cmds_list->var_data->absolute_path, \
				prog_data->cmds_list->var_data->cmd_argument, envp) == -1)
			{
				ft_dllst_clear(prog_data->cmds_list);
				perror(NULL);
				exit(errno);
			}
		}
		waitpid(0, NULL, 0);
		prog_data->cmds_list = prog_data->cmds_list->next;
	}
	return (0);
}
