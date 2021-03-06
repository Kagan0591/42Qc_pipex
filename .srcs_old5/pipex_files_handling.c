/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_files_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 09:51:03 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/13 10:46:55 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int	open_files(t_data *prog_data, int argc, char **argv)
{
	if (access(argv[argc - 1], R_OK | W_OK) == -1 && errno != ENOENT)
	{
		dprintf(2, "A probleme occured when opening the file: %s\n", argv[argc - 1]);
		exit(1); //The program exit without doing anything else and return the code 2
	}
	prog_data->filesfd[1] = open(argv[(argc - 1)], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
	if (prog_data->here_doc_flag == 1)
	{
		prog_data->here_doc_tmp_fd = open("here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
		return (0);
	}
	else if (access(argv[1], R_OK) == -1)
	{
		dprintf(2, "A probleme occured when opening the file: %s\n", argv[1]);
		return (2); // Returning 2 to the parent function, to skip all the cmd except the last one
	}
	else
		prog_data->filesfd[0] = open(argv[1], O_RDONLY, O_WRONLY);
	return (0);
}
