/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 10:37:56 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/27 12:56:26 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLY_LINKED_LIST_H
# define DOUBLY_LINKED_LIST_H

typedef enum t_bool
{
	false,
	true
}t_bool;

typedef struct t_cmdinfos
{
	char				*absolute_path;
	char				**cmd_argument;
	struct t_cmdinfos	*next;
	struct t_cmdinfos	*previous;
}t_cmdinfos;

t_cmdinfos	*ft_dllst_new(char *absolute_path, char **cmd_argument);
t_cmdinfos	*ft_dllst_add_front(t_cmdinfos *p_lst, char *absolute_path, char **cmd_argument);
t_cmdinfos	*ft_dllst_add_back(t_cmdinfos *p_lst, char *absolute_path, char **cmd_argument);
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
