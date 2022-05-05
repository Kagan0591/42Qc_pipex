/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 09:33:33 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/04 12:26:12 by tchalifo         ###   ########.fr       */
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
	t_data	*prg_data;
	int	fork_pid;
	int	fork_pid2;

	prg_data = mem_init();
	if (open_files(prg_data, argc, argv) == 2)
		prg_data->mainloop_i = argc - 2; //Pour commencer avec le dernier cmd en cas d absence de fichier input
	else
		prg_data->mainloop_i = 2;
	while (prg_data->mainloop_i <= (argc - 2)) // -1 pour l'align tab et -1 pour skip de dernier fichier outfile
	{
		pipe(prg_data->pipefd);
		fork_pid = fork();
		if (prg_data->mainloop_i == 2)
		{
			if (fork_pid != 0)//Parent fork 1 (main process)
			{
				fork_pid2 = fork();

				if(fork_pid2 != 0)//Parent fork 2 (main process)
				{
					waitpid(fork_pid2, NULL, 0);
					prg_data->mainloop_i++;
				}
				else//Child fork 2
				{
					waitpid(fork_pid, NULL, 0);
					prg_data->mainloop_i++;
					setup_io_child_proc_1(prg_data, argc);
					dprintf(2, "argv passed to function ft_execve child 2 = %s\n", argv[prg_data->mainloop_i]);
					if (ft_execve(argv[prg_data->mainloop_i], envp) == -1)
						exit(3);
				}
			}
			else//Child fork 1
			{
				setup_io_child_proc_1(prg_data, argc);
				dprintf(2, "argv passed to function ft_execve child 1 = %s\n", argv[prg_data->mainloop_i]);
				if (ft_execve(argv[prg_data->mainloop_i], envp) == -1)
					exit(3);
			}
		}
		// else if (prg_data->mainloop_i > 2)
		// {
			//the pipe call need to be between the to process, first is reading the last incrementation
			//pipe and second writing for the next incrementation of the loop
		// }
		prg_data->mainloop_i++;
	}
	return (0);
}
