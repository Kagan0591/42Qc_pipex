/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_files_handling_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:48:55 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/18 18:48:59 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_include/pipex_bonus.h"

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
	if (access(argv[argc - 1], R_OK | W_OK) == -1 && errno != ENOENT)
	{
		perror(NULL);
		exit(errno);
	}
	else if (prog_data->here_doc_flag == 1)
		prog_data->filesfd[1] = open(argv[(argc - 1)], \
			O_WRONLY | O_CREAT | O_APPEND, S_IRWXU | S_IRWXG | S_IRWXO);
	else
		prog_data->filesfd[1] = open(argv[(argc - 1)], \
			O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
}
