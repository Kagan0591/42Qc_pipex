/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 09:33:33 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/27 20:16:27 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* RETURN VALUE
 * If a -1 is returned, data structure initialisation probleme occured.
 *
 *
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
	while (prg_data->mainloop_i < (argc - 2)) // -1 pour l'align tab et -1 pour skip de dernier fichier outfile
	{
		pipe(prg_data->pipefd);
		fork_pid = fork();
		if (fork_pid != 0) //PARENT PROCESS
		{
			setupio(prg_data, fork_pid, argc);
			wait(NULL);
		}
		if (fork_pid == 0) // CHILD PROCESS
		{
			setupio(prg_data, fork_pid, argc);
			dprintf(2, "argv passed to function ft_execve = %s\n", argv[prg_data->mainloop_i]);
			if (ft_execve(argv[prg_data->mainloop_i], envp) == -1)
				exit(3);
		}
		else
			wait(NULL);
		prg_data->mainloop_i++;
	}
	close(prg_data->filesfd[0]);
	close(prg_data->filesfd[1]);
	return (0);
}








// 		pipe(prg_data->pipefd);
// 		fork_pid = fork();
// 		if (fork_pid != 0)
// 		{
// 			close(prg_data->pipefd[WRITE_ENDPIPE]);
// 			if (i == 2) // Premier iteration le input doit etre rediriger vers le fichier intest ouvert plustot
// 			{
// 				dup2(prg_data->filesfd[0], 0);
// 				close(prg_data->filesfd[0]);
// 			}
// 			else
// 			{
// 				dup2(prg_data->pipefd[READ_ENDPIPE], 0);
// 				close(prg_data->pipefd[READ_ENDPIPE]);
// 			}
// 		}
// 		if (fork_pid == 0) //Child process
// 		{
// 			close(prg_data->pipefd[READ_ENDPIPE]);
// 			if (i == (argc - 2)) // Derniere iteration le WRITE_ENDPIPE doit etre rediriger vers le fichier outtest ouvert plustot
// 			{
// 				perror("TEST 1\n");
// 				dup2(prg_data->filesfd[1], 1);
// 				close(prg_data->filesfd[1]);
// 			}
// 			else
// 			{
// 				perror("TEST 2\n");
// 				dup2(prg_data->pipefd[WRITE_ENDPIPE], 1);
// 				close(prg_data->pipefd[WRITE_ENDPIPE]);
// 			}
// 			if (execution(argv[i], envp) == -1)
// 			{
// 				perror("Exec probleme\n");
// 				exit(2);
// 			}
// 		}
// 		waitpid(-1, NULL, 0);
// 		i++;
// 		perror("WHILE LOOP PASS : \n");
// 	}
// 	close(fd_data->filesfd[0]);
// 	close(fd_data->filesfd[1]);
// 	return (0);
// }
