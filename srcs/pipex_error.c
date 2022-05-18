/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:36:23 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/18 13:47:26 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int	exit_args_limit(void)
{
	perror("Bad number of arguments, try something like < ./pipex infile cmd cmd outfile >\n");
	return (1);
}