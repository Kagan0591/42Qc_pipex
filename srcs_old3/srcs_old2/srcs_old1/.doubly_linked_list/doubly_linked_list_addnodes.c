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

t_exec	*ft_dllst_new(char *bin_path, char**bin_arguments)
{
	t_exec	*new_node;

	new_node = malloc(sizeof(t_exec));
	if (new_node)
	{
		new_node->bin_path = bin_path;
		new_node->bin_arguments = bin_arguments;
		new_node->next = NULL;
		new_node->previous = NULL;
	}
	return (new_node);
}

t_exec	*ft_dllst_add_back(t_exec *p_lst, char *bin_path, char**bin_arguments)
{
	t_exec	*new_node;

	if (!p_lst)
		return (ft_dllst_new(bin_path, bin_arguments));
	new_node = malloc(sizeof(t_exec));
	if (new_node)
	{
		while (p_lst->next != NULL)
			p_lst = p_lst->next;
		new_node->bin_path = bin_path;
		new_node->bin_arguments = bin_arguments;
		new_node->next = NULL;
		new_node->previous = p_lst;
		p_lst->next = new_node;
		while (p_lst->previous != NULL)
			p_lst = p_lst->previous;
		return (p_lst);
	}
	return (NULL);
}
