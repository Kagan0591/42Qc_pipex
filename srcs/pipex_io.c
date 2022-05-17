/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:21:05 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/17 17:11:38 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup_input(t_data *prog_data)
{
	if (prog_data->cmds_list->previous == NULL)
	{
		if (prog_data->here_doc_flag == 1)
		{
			dprintf(2, "La premiere execution apres le here_doc TEST READ\n");
			close(prog_data->here_doc_pipefd[WRITE_ENDPIPE]);
			dup2(prog_data->here_doc_pipefd[READ_ENDPIPE], 0);
			close(prog_data->here_doc_pipefd[READ_ENDPIPE]);
		}
		else if (prog_data->infile_flag == 1)
		{
		}
		else
		{
			dup2(prog_data->filesfd[0], 0);
			close(prog_data->filesfd[0]);
		}
	}
	else
	{
		dprintf(2, "Les autres execution TEST READ\n");
		close(prog_data->pipefd[WRITE_ENDPIPE]);
		dup2(prog_data->pipefd[READ_ENDPIPE], 0);
		close(prog_data->pipefd[READ_ENDPIPE]);
	}
}

void	setup_output(t_data *prog_data)
{
	if (prog_data->cmds_list->next == NULL)
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
