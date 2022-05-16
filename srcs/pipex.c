/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 09:33:33 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/16 11:28:01 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* RETURN VALUE
 * If a 0 is returned, the programm terminate correcly
 * If a 1 is returned, A probleme occured when opening the last file.
 * If a 2 is returned, data structure initialisation probleme occured.
 * If a 3 is returned, execve probleme occured.
 */
#include "include/pipex.h"

static int	here_doc(t_data *prog_data, char *limiter)
{
	char *here_doc_tmp = NULL;

	pipe(prog_data->here_doc_pipefd);
	here_doc_tmp = get_next_line(0);
	while (ft_strncmp(here_doc_tmp, limiter, ft_strlen(limiter)) != 0)
	{
		ft_putstr_fd(here_doc_tmp, prog_data->here_doc_pipefd[WRITE_ENDPIPE]);
		free(here_doc_tmp);
		here_doc_tmp = get_next_line(0);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	prog_data;
	int		i;

	prog_data = struct_mem_init(argc);
	i = 2;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		prog_data.here_doc_flag = 1;
		here_doc(&prog_data, argv[2]);
		i = 3;
	}
	if(open_files(&prog_data, argc, argv) == 2)
	{
		i = argc - 2;
		prog_data.infile_flag = 1;
	}
	while (i < argc - 1)
	{
		prog_data.cmds_list = ft_dllst_add_back(prog_data.cmds_list);
		prog_data.cmds_list = ft_dllist_go_to_right(prog_data.cmds_list);
		cmd_parsing(prog_data.cmds_list->var_data, argv[i], envp);
		i++;
	}
	prog_data.cmds_list = prog_data.cmds_list->first_elem;
	execution_time(&prog_data, envp);
	return (0);
}
