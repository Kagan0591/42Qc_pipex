/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_files_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 09:51:03 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/27 12:47:12 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int	open_files(t_data *p_fd_data, int argc, char **p_argv)
{
	if (access(p_argv[1], R_OK) == -1)
	{
		dprintf(2, "Permission denied: %s\n", p_argv[1]);
		exit(1);
	}
	p_fd_data->filesfd[0] = open(p_argv[1], O_RDONLY);
	if (p_fd_data->filesfd[0] == -1)
	{
		dprintf(2, "No such file or directory: %s\n", p_argv[1]);
		return (2);
	}
	p_fd_data->filesfd[1] = open(p_argv[(argc - 1)], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
	return (0);
}
