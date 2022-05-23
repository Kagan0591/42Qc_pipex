/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list_bonus.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:47:08 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/21 22:20:20 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLY_LINKED_LIST_BONUS_H
# define DOUBLY_LINKED_LIST_BONUS_H

typedef enum t_bool
{
	false,
	true
}t_bool;

typedef struct t_cmdinfos_data
{
	char				*absolute_path;
	char				**cmd_argument;
	int					fork_pid;
	int					index;
}t_cmdinfos_data;

typedef struct t_cmdinfos
{
	t_cmdinfos_data		*var_data;
	struct t_cmdinfos	*next;
	struct t_cmdinfos	*previous;
}t_cmdinfos;

t_cmdinfos	*ft_dllst_new(void);
t_cmdinfos	*ft_dllst_add_back(t_cmdinfos *p_lst);
void		ft_dllst_delone(t_cmdinfos *p_lst);
void		ft_dllst_clear(t_cmdinfos *p_lst);
void		ft_dllst_secure_del(t_cmdinfos *p_lst);
t_bool		ft_dllst_isempty(t_cmdinfos *p_lst);
int			ft_dllst_size(t_cmdinfos *p_lst);
void		ft_dllst_print_single_node(t_cmdinfos *p_lst);
void		ft_dllst_print_lst(t_cmdinfos *p_lst);
t_cmdinfos	*ft_dllist_go_to_left(t_cmdinfos *p_lst);
t_cmdinfos	*ft_dllist_go_to_right(t_cmdinfos *p_lst);

#endif
