/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:36:23 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/21 22:23:21 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int	exit_args_limit(void)
{
	write(2, "Bad number of arguments, try something like \
		./pipex infile cmd cmd outfile \n", 78);
	return (1);
}
