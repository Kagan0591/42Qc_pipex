/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 10:37:56 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/25 21:59:26 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLY_LINKED_LIST_H
# define DOUBLY_LINKED_LIST_H

typedef enum t_bool
{
	false,
	true
}t_bool;

typedef struct t_data
{
	int	filesfd[2];
	int	int	pipefd[2];

}t_data;

typedef struct t_dlinklst
{
	/*data*/
	struct s_dlinkls	*next;
	struct s_dlinklst	*previous;
}t_dlinklst;

t_dlinklst	*ft_dllst_new(/*data*/);
t_dlinklst	*ft_dllst_add_front(t_dlinklst *p_lst, /*data*/);
t_dlinklst	*ft_dllst_add_back(t_dlinklst *p_lst, /*data*/);
void		ft_dllst_delone(t_dlinklst *p_lst);
void		ft_dllst_clear(t_dlinklst *p_lst);
void		ft_dllst_secure_del(t_dlinklst *p_lst);
t_bool		ft_dllst_isempty(t_dlinklst *p_lst);
int			ft_dllst_size(t_dlinklst *p_lst);
void		ft_dllst_print_single_node(t_dlinklst *p_lst);
void		ft_dllst_print_lst(t_dlinklst *p_lst);
t_dlinklst	*ft_dllist_go_to_left(t_dlinklst *p_lst);
t_dlinklst	*ft_dllist_go_to_right(t_dlinklst *p_lst);

#endif
