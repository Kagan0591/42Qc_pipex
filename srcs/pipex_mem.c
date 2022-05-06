/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:01:50 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/06 15:59:50 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"
static void	mem_init(t_data **prog_data, int argc)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		(*prog_data)->filesfd[i] = -1;
		i++;
	}
	(*prog_data)->mainloop_i = 0;
	(*prog_data)->cmds_list->var_data->absolute_path = NULL;
	(*prog_data)->cmds_list->var_data->cmd_argument = malloc(sizeof(char *) * (argc - 3));
}

t_data	*struct_mem_init(int argc)
{
	t_data	*prog_data;

	prog_data = malloc(sizeof(t_data));
	if (!prog_data)
	{
		dprintf(2, "Memory allocation probleme. Exit program, Bye!\n");
		exit (1);
	}
	prog_data->cmds_list = malloc(sizeof(t_cmdinfos));
	if (!prog_data->cmds_list)
	{
		dprintf(2, "Memory allocation probleme. Exit program, Bye!\n");
		exit (1);
	}
	prog_data->cmds_list->var_data = malloc(sizeof(t_cmdinfos_data));
	if (!prog_data->cmds_list->var_data)
	{
		dprintf(2, "Memory allocation probleme. Exit program, Bye!\n");
		exit (1);
	}
	mem_init(&prog_data, argc);
	return (prog_data);
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
