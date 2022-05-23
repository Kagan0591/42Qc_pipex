/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:48:39 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/22 20:39:09 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_include/pipex_bonus.h"

int	exit_args_limit(void)
{
	write(2, "Bad number of arguments, try something like \
		./pipex infile cmd cmd outfile \n", 78);
	return (1);
}
