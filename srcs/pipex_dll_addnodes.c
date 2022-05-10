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

t_cmdinfos	*ft_dllst_new()
{
	t_cmdinfos	*new_node;

	new_node = ft_calloc(1, sizeof(t_cmdinfos));
	if (new_node)
	{
		new_node->var_data = malloc(sizeof(t_cmdinfos_data));
		new_node->first_elem = new_node;
		new_node->var_data->fork_pid = -1;
		new_node->var_data->index = 1;
	}
	return (new_node);
}

t_cmdinfos	*ft_dllst_add_back(t_cmdinfos *p_lst)
{
	t_cmdinfos	*new_node;

	if (!p_lst)
		return (ft_dllst_new());
	new_node = ft_calloc(1, sizeof(t_cmdinfos));
	if (new_node)
	{
		new_node->first_elem = p_lst->first_elem;
		while (p_lst->next != NULL)
			p_lst = p_lst->next;
		new_node->var_data = malloc(sizeof(t_cmdinfos_data));
		new_node->var_data->fork_pid = -1;
		new_node->previous = p_lst;
		p_lst->next = new_node;
		while (p_lst->previous != NULL)
			p_lst = p_lst->previous;
		new_node->var_data->index = (ft_dllst_size(p_lst));
		return (p_lst);
	}
	return (NULL);
}
