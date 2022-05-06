/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list_addnodes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:13:55 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/18 11:13:55 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmdinfos	*ft_dllst_new(char *absolute_path_data, char**cmd_argument_data, int *pipe_data)
{
	t_cmdinfos	*new_node;
	int			i;

	i = 0;
	new_node = malloc(sizeof(t_cmdinfos));
	if (new_node)
	{
		new_node->var_data->absolute_path = absolute_path_data;
		new_node->var_data->cmd_argument = cmd_argument_data;
		while (i < 2)
		{
			new_node->var_data->pipefd[i] = pipe_data[i];
			i++;
		}
		new_node->next = NULL;
		new_node->previous = NULL;
	}
	return (new_node);
}

t_cmdinfos	*ft_dllst_add_back(t_cmdinfos *p_lst, char *absolute_path, char**cmd_argument, int *pipe_data)
{
	t_cmdinfos	*new_node;
	int			i;

	i = 0;
	if (!p_lst)
		return (ft_dllst_new(absolute_path, cmd_argument, pipe_data));
	new_node = malloc(sizeof(t_cmdinfos));
	if (new_node)
	{
		while (p_lst->next != NULL)
			p_lst = p_lst->next;
		new_node->var_data->absolute_path = absolute_path;
		new_node->var_data->cmd_argument = cmd_argument;
		while (i < 2)
		{
			new_node->var_data->pipefd[i] = pipe_data[i];
			i++;
		}
		new_node->next = NULL;
		new_node->previous = p_lst;
		p_lst->next = new_node;
		return (p_lst);
	}
	return (NULL);
}
