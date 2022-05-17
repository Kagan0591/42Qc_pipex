/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:01:50 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/17 18:05:28 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	struct_mem_init(void)
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
