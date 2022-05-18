/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_io_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:21:05 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/18 18:01:29 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_include/pipex_bonus.h"

void	setup_input(t_data *prog_data)
{
	if (prog_data->cmds_list->previous == NULL)
	{
		if (prog_data->here_doc_flag == 1)
		{
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
		close(prog_data->pipefd[WRITE_ENDPIPE]);
		dup2(prog_data->pipefd[READ_ENDPIPE], 0);
		close(prog_data->pipefd[READ_ENDPIPE]);
	}
}

void	setup_output(t_data *prog_data)
{
	if (prog_data->cmds_list->next == NULL)
	{
		dup2(prog_data->filesfd[1], 1);
		close(prog_data->filesfd[1]);
	}
	else
	{
		close(prog_data->pipefd[READ_ENDPIPE]);
		dup2(prog_data->pipefd[WRITE_ENDPIPE], 1);
		close(prog_data->pipefd[WRITE_ENDPIPE]);
	}
}
