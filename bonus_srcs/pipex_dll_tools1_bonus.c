/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_dll_tools1_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:48:31 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/18 18:48:31 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_include/pipex_bonus.h"

int	ft_dllst_size(t_cmdinfos *p_lst)
{
	int	count;

	count = 0;
	while (p_lst != NULL)
	{
		count++;
		p_lst = p_lst->next;
	}
	return (count);
}

t_cmdinfos	*ft_dllist_go_to_left(t_cmdinfos *p_lst)
{
	while (p_lst->previous != NULL)
		p_lst = p_lst->previous;
	return (p_lst);
}

t_cmdinfos	*ft_dllist_go_to_right(t_cmdinfos *p_lst)
{
	while (p_lst->next != NULL)
		p_lst = p_lst->next;
	return (p_lst);
}
