/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:01:50 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/12 10:37:53 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

t_data	struct_mem_init()
{
	t_data	prog_data;

	prog_data.filesfd[0] = 0;
	prog_data.filesfd[1] = 0;
	prog_data.pipefd[0] = 0;
	prog_data.pipefd[1] = 0;
	prog_data.mainloop_i = 0;
	prog_data.here_doc_flag = 0;
	prog_data.cmds_list = NULL;
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
