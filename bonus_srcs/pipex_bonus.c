/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:48:03 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/18 18:48:05 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_include/pipex_bonus.h"

static int	here_doc(t_data *prog_data, char *limiter)
{
	char	*here_doc_tmp;

	here_doc_tmp = NULL;
	if (pipe(prog_data->here_doc_pipefd) == -1)
	{
		perror(NULL);
		exit(errno);
	}
	here_doc_tmp = get_next_line(0);
	while (ft_strncmp(here_doc_tmp, limiter, ft_strlen(limiter)) != 0)
	{
		ft_putstr_fd(here_doc_tmp, prog_data->here_doc_pipefd[WRITE_ENDPIPE]);
		free(here_doc_tmp);
		here_doc_tmp = get_next_line(0);
	}
	return (0);
}

static void	build_cmd_list(t_data *prog_data, int incrementor)
{
	while (incrementor < (prog_data->argc - 1))
	{
		prog_data->cmds_list = ft_dllst_add_back(prog_data->cmds_list);
		if (ft_dllst_size(prog_data->cmds_list) == 1)
			prog_data->first_node_ptr = prog_data->cmds_list;
		prog_data->cmds_list = ft_dllist_go_to_right(prog_data->cmds_list);
		cmd_parsing(prog_data->cmds_list->var_data, \
			prog_data->argv[incrementor], prog_data->envp);
		incrementor++;
	}
	prog_data->cmds_list = ft_dllist_go_to_left(prog_data->cmds_list);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	prog_data;
	int		i;

	prog_data = struct_mem_init(argc, argv, envp);
	i = 2;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		prog_data.here_doc_flag = 1;
		here_doc(&prog_data, argv[2]);
		i = 3;
	}
	if (open_infile(&prog_data, argv) == 2)
	{
		i = 3;
		prog_data.infile_flag = 1;
	}
	open_outfile(&prog_data, argc, argv);
	build_cmd_list(&prog_data, i);
	execution_time(&prog_data, envp);
	prog_data.cmds_list = prog_data.first_node_ptr;
	ft_dllst_clear(prog_data.cmds_list);
	return (0);
}
