/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_linked_list.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 10:37:56 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/06 13:43:47 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLY_LINKED_LIST_H
# define DOUBLY_LINKED_LIST_H

typedef enum t_bool
{
	false,
	true
}t_bool;

typedef struct t_cmdinfos_data
{
	char				*absolute_path;
	char				**cmd_argument;
	int					pipefd[2]; //fd[0] = read | fd[1] = write
}t_cmdinfos_data;

typedef struct t_cmdinfos
{
	t_cmdinfos_data		*var_data;
	struct t_cmdinfos	*next;
	struct t_cmdinfos	*previous;
}t_cmdinfos;

t_cmdinfos	*ft_dllst_new(char *absolute_path_data, char**cmd_argument_data, int *pipe_data);
t_cmdinfos	*ft_dllst_add_back(t_cmdinfos *p_lst, char *absolute_path, char**cmd_argument, int *pipe_data);
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
