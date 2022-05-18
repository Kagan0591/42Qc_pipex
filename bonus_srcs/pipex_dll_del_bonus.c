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

#include "bonus_include/pipex_bonus.h"

void	ft_dllst_delone(t_cmdinfos *p_lst)
{
	if (p_lst)
	{
		clear_char_tab(p_lst->var_data->cmd_argument);
		free(p_lst->var_data->absolute_path);
		free(p_lst->var_data);
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

t_bool	ft_dllst_isempty(t_cmdinfos *p_lst)
{
	if (p_lst == NULL)
		return (true);
	return (false);
}
