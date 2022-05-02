/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 09:33:33 by tchalifo          #+#    #+#             */
/*   Updated: 2022/05/02 09:37:15 by tchalifo         ###   ########.fr       */
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

	prg_data = mem_init();
	if (open_files(prg_data, argc, argv) == 2)
		prg_data->mainloop_i = argc - 2; //Pour commencer avec le dernier cmd en cas d absence de fichier input
	else
		prg_data->mainloop_i = 2;
	pipe(prg_data->pipefd);
	while (prg_data->mainloop_i <= (argc - 2)) // -1 pour l'align tab et -1 pour skip de dernier fichier outfile
	{
		fork_pid = fork();
		if (fork_pid == 0) //CHILD PROCESS
		{
			setupio(prg_data, fork_pid, argc);
			dprintf(2, "argv passed to function ft_execve = %s\n", argv[prg_data->mainloop_i]);
			if (ft_execve(argv[prg_data->mainloop_i], envp) == -1)
				exit(3);
		}
		else //PARENT PROCESS
			wait(NULL);
		prg_data->mainloop_i++;
	}
	return (0);
}
