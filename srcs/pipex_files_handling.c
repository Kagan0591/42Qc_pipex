/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_files_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 09:51:03 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/19 12:25:51 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int	open_infile(t_data *prog_data, char **argv)
{
	if (access(argv[1], R_OK) == -1)
	{
		if (prog_data->here_doc_flag == 1)
			return (0);
		perror(NULL);
		return (2);
	}
	else
	{
		prog_data->filesfd[0] = open(argv[1], O_RDONLY, O_WRONLY);
		if (prog_data->filesfd[0] == -1)
		{
			perror(NULL);
			exit(errno);
		}
	}
	return (0);
}

void	open_outfile(t_data *prog_data, int argc, char **argv)
{
	if (access(argv[argc - 1], W_OK) == -1 && errno != ENOENT)
	{
		perror(NULL);
		exit(errno);
	}
	else if (prog_data->here_doc_flag == 1)
		prog_data->filesfd[1] = open(argv[(argc - 1)], \
			O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IWGRP | S_IWOTH);
	else
		prog_data->filesfd[1] = open(argv[(argc - 1)], \
			O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IWGRP | S_IWOTH);
}
