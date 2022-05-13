/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:47:34 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/18 14:38:52 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	trimmed_path = path_env_var_to_str(p_envp);
	splitted_path = ft_split(trimmed_path, ':');
	while (splitted_path[i])
	{
		if (access(ft_strjoin(splitted_path[i], bin_name), X_OK) != -1)
		{
			complete_bin_path = ft_strjoin(splitted_path[i], bin_name);
			clear_char_tab(splitted_path, ft_strofstrlen(splitted_path));
			free((void*)trimmed_path);
			return (complete_bin_path);
		}
		i++;
	}
	clear_char_tab(splitted_path, ft_strofstrlen(splitted_path));
	free((void*)trimmed_path);
	return (NULL);
}

int	fill_in_exec_struct(char *bin_n_option, t_exec *cmd_datastruct, char **p_envp)
{
	int		i;
	int		j;
	char	*bin_path;

	bin_path = recup_the_bin_path(bin_n_option[0], p_envp);
	if (!bin_path)
		return (-1);
	cmd_datastruct = ft_dllst_add_back(cmd_datastruct, bin_path, NULL);
	cmd_datastruct->bin_arguments = malloc(sizeof(char*) * ft_strlen(bin_n_option));
	if (!cmd_datastruct->bin_arguments)
		return (-1);
	i = 1;
	j = 0;
	while (bin_n_option[i] != NULL)
	{
		cmd_datastruct->bin_arguments[j] = malloc(sizeof(char) * ft_strlen(bin_n_option[i]));
		cmd_datastruct->bin_arguments[j] = bin_n_option[i];
		i++;
		j++;
	}
	return (0);
}

