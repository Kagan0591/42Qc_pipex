/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 09:33:33 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/12 14:11:09 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* RETURN VALUE
 * If a 0 is returned, the programm terminate correcly
 * If a 1 is returned, A probleme occured when opening the last file.
 * If a 2 is returned, data structure initialisation probleme occured.
 * If a 3 is returned, execve probleme occured.
 */
#include "include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	prog_data;

	prog_data = struct_mem_init(argc);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		prog_data.here_doc_flag = 1;
		open_files(&prog_data, argc, argv);
		here_doc(&prog_data, argv[2]);
		prog_data.mainloop_i = 3;
	}
	else if (open_files(&prog_data, argc, argv) == 2)
		prog_data.mainloop_i = argc - 2; //Pour commencer avec le dernier cmd en cas d absence de fichier input
	else
		prog_data.mainloop_i = 2;
	while (prog_data.mainloop_i < argc - 1)
	{
		prog_data.cmds_list = ft_dllst_add_back(prog_data.cmds_list);
		prog_data.cmds_list = ft_dllist_go_to_right(prog_data.cmds_list);
		cmd_parsing(prog_data.cmds_list->var_data, argv[prog_data.mainloop_i], envp);
		prog_data.mainloop_i++;
	}
	prog_data.cmds_list = prog_data.cmds_list->first_elem;
	execution_time(&prog_data, envp);
	return (0);
}

int	here_doc(t_data *prog_data, char *limiter)
{
	char *here_doc_tmp = NULL;

	prog_data->here_doc_tmp_fd = open("here_doc_tmp",\
	 O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);

	here_doc_tmp = get_next_line(0);
	while (ft_strncmp(here_doc_tmp, limiter, ft_strlen(limiter)) != 0)
	{
		if (here_doc_tmp)
		{
			write(prog_data->here_doc_tmp_fd, here_doc_tmp, (ft_strlen(here_doc_tmp) - 1));
			free(here_doc_tmp);
		}
		here_doc_tmp = get_next_line(0);
	}
	return (0);
}

//int	gnl_stdin_read_loop()
