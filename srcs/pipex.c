/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 09:33:33 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/23 12:21:12 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

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
	if (prog_data->cmds_list)
		prog_data->cmds_list = ft_dllist_go_to_left(prog_data->cmds_list);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	prog_data;
	int		i;

	if (argc != 5)
		return (exit_args_limit());
	prog_data = struct_mem_init(argc, argv, envp);
	i = 2;
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
