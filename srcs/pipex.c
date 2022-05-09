/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 09:33:33 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/09 16:19:37 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* RETURN VALUE
 * If a 0 is returned, the programm terminate correcly
 * If a 1 is returned, A probleme occured when opening the last file.
 * If a 2 is returned, data structure initialisation probleme occured.
 * If a 3 is returned, execve probleme occured.
 */
#include "include/pipex.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	*prg_data;
// 	int	fork_pid;
// 	int	fork_pid2;

// 	prg_data = mem_init();
// 	if (open_files(prg_data, argc, argv) == 2)
// 		prg_data->mainloop_i = argc - 2; //Pour commencer avec le dernier cmd en cas d absence de fichier input
// 	else
// 		prg_data->mainloop_i = 2;
// 	while (prg_data->mainloop_i <= (argc - 2)) // -1 pour l'align tab et -1 pour skip de dernier fichier outfile
// 	{
// 		pipe(prg_data->pipefd);
// 		fork_pid = fork();
// 		if (prg_data->mainloop_i == 2)
// 		{
// 			if (fork_pid != 0)//Parent fork 1 (main process)
// 			{
// 				fork_pid2 = fork();

// 				if(fork_pid2 != 0)//Parent fork 2 (main process)
// 				{
// 					waitpid(fork_pid2, NULL, 0);
// 					prg_data->mainloop_i++;
// 				}
// 				else//Child fork 2
// 				{
// 					waitpid(fork_pid, NULL, 0);
// 					prg_data->mainloop_i++;
// 					setup_io(prg_data, argc);
// 					//dprintf(2, "argv passed to function ft_execve child 2 = %s\n", argv[prg_data->mainloop_i]);
// 					if (ft_execve(argv[prg_data->mainloop_i], envp) == -1)
// 						exit(3);
// 				}
// 			}
// 			else//Child fork 1
// 			{
// 				setup_io(prg_data, argc);
// 				//dprintf(2, "argv passed to function ft_execve child 1 = %s\n", argv[prg_data->mainloop_i]);
// 				if (ft_execve(argv[prg_data->mainloop_i], envp) == -1)
// 					exit(3);
// 			}
// 		}
// 		prg_data->mainloop_i++;
// 	}
// 	close(prg_data->pipefd[0]);
// 	close(prg_data->pipefd[1]);

// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	t_data	prog_data;

	prog_data = struct_mem_init(argc);
	if (open_files(&prog_data, argc, argv) == 2)
		prog_data.mainloop_i = argc - 2; //Pour commencer avec le dernier cmd en cas d absence de fichier input
	else
		prog_data.mainloop_i = 2;
	while (prog_data.mainloop_i < argc -1)
	{
		prog_data.cmds_list = ft_dllst_add_back(prog_data.cmds_list);
		cmd_parsing(prog_data.cmds_list->var_data, argv[prog_data.mainloop_i], envp);
		prog_data.mainloop_i++;
	}
	prog_data.cmds_list = prog_data.cmds_list->first_elem;
	while (prog_data.cmds_list->next != NULL)
	{
		setup_input(&prog_data);
		if (pipe(prog_data.pipefd) == -1)
			perror("Pipe probleme\n");
		prog_data.cmds_list->var_data->fork_pid = fork();

		setup_output(&prog_data, argc);
		execution_time(prog_data.cmds_list->var_data, envp);
	}
	return (0);
}