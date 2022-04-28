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

t_cmdinfos	*ft_dllst_new(char *absolute_path, char**cmd_argument)
{
	t_cmdinfos	*new_node;

	new_node = malloc(sizeof(t_cmdinfos));
	if (new_node)
	{
		new_node->absolute_path = absolute_path;
		new_node->cmd_argument = cmd_argument;
		new_node->next = NULL;
		new_node->previous = NULL;
	}
	return (new_node);
}

t_cmdinfos	*ft_dllst_add_back(t_cmdinfos *p_lst, char *absolute_path, char**cmd_argument)
{
	t_cmdinfos	*new_node;

	if (!p_lst)
		return (ft_dllst_new(absolute_path, cmd_argument));
	new_node = malloc(sizeof(t_cmdinfos));
	if (new_node)
	{
		while (p_lst->next != NULL)
			p_lst = p_lst->next;
		new_node->absolute_path = absolute_path;
		new_node->cmd_argument = cmd_argument;
		new_node->next = NULL;
		new_node->previous = p_lst;
		p_lst->next = new_node;
		return (p_lst);
	}
	return (NULL);
}
