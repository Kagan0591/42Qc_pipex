/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:35:38 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/17 13:35:38 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define READ_ENDPIPE 0
# define WRITE_ENDPIPE 1

# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdio.h>
# include "libft.h"
# include "doubly_linked_list.h"

typedef struct t_data
{
	int			filesfd[2];
	int			infile_flag;
	int			pipefd[2];
	int			here_doc_flag;
	int			here_doc_pipefd[2];
	t_cmdinfos	*first_node_ptr;
	t_cmdinfos	*cmds_list;
	int			argc;
	char		**argv;
	char		**envp;
}t_data;

t_data	struct_mem_init(int argc, char **argv, char **envp);
void	clear_char_tab(char **tab);
int		open_infile(t_data *prog_data, char **argv);
void	open_outfile(t_data *prog_data, int argc, char **argv);
void	cmd_parsing(t_cmdinfos_data *exec_data, char *p_argv, char **envp);
int		execution_time(t_data *prog_data, char **envp);
void	setup_input(t_data *prog_data);
void	setup_output(t_data *prog_data);
int		exit_args_limit(void);

#endif
