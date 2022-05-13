/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list_del.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:14:33 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/18 11:14:33 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

void	ft_dllst_delone(t_cmdinfos *p_lst)
{
	if (p_lst)
	{
		ft_dllst_secure_del(p_lst);
		/*free_tabs*/
		free(p_lst);
	}
}

void	ft_dllst_clear(t_cmdinfos *p_lst)
{
	t_cmdinfos	*tmp;

	tmp = NULL;
	while (p_lst != NULL)
	{
		tmp = p_lst->next;
		ft_dllst_delone(p_lst);
		p_lst = tmp;
	}
}

void	ft_dllst_secure_del(t_cmdinfos *p_lst)
{
	(void) p_lst;
	/*data to delete*/
}

t_bool	ft_dllst_isempty(t_cmdinfos *p_lst)
{
	if (p_lst == NULL)
		return (true);
	return (false);
}
