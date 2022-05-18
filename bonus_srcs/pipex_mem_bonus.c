/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mem_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:01:50 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/18 18:01:36 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_include/pipex_bonus.h"

t_data	struct_mem_init(int argc, char **argv, char **envp)
{
	t_data	prog_data;

	prog_data.filesfd[0] = 0;
	prog_data.filesfd[1] = 0;
	prog_data.infile_flag = 0;
	prog_data.pipefd[0] = 0;
	prog_data.pipefd[1] = 0;
	prog_data.here_doc_pipefd[0] = 0;
	prog_data.here_doc_pipefd[1] = 0;
	prog_data.here_doc_flag = 0;
	prog_data.cmds_list = NULL;
	prog_data.first_node_ptr = NULL;
	prog_data.argc = argc;
	prog_data.argv = argv;
	prog_data.envp = envp;
	return (prog_data);
}

void	clear_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
}
