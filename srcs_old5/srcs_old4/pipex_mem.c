/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:01:50 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/27 14:02:46 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

t_data	*mem_init(void)
{
	t_data	*prg_data;

	prg_data = malloc(sizeof(t_data));
	if (!prg_data)
	{
		dprintf(2, "Memory allocation probleme. Exit program, Bye!\n");
		exit (1);
	}
	prg_data->cmds_list = NULL;
	prg_data->mainloop_i = 0;
	return (prg_data);
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
