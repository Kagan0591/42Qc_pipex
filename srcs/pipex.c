/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 09:33:33 by tchalifo          #+#    #+#             */
/*   Updated: 2022/04/26 12:03:28 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

static char	*path_env_var_to_str(char **p_envp)
{
	int		i;

	i = 0;
	if (p_envp)
	{
		while (p_envp[i] != NULL)
		{
			if (strncmp(p_envp[i], "PATH=", 5) == 0)
				return (ft_strtrim(p_envp[i], "PATH="));
			i++;
		}
	}
	return (NULL);
}

char	*recup_the_bin_path(char *bin_name, char **p_envp)
{
	char	**splitted_path;
	char	*trimmed_path;
	char	*complete_bin_path;
	int		i;

	i = 0;
	complete_bin_path = NULL;
	trimmed_path = path_env_var_to_str(p_envp);
	splitted_path = ft_split(trimmed_path, ':');
	free(trimmed_path);
	while (splitted_path[i])
	{
		complete_bin_path = ft_strjoin(splitted_path[i], "/");
		complete_bin_path = ft_strjoin(complete_bin_path, bin_name);
		if (access(complete_bin_path, X_OK) != -1)
		{
			clear_char_tab(splitted_path);
			return (complete_bin_path);
		}
		i++;
	}
	free (complete_bin_path);
	clear_char_tab(splitted_path);
	return (NULL);
}

static int	execution(char *p_argv, char **p_envp)
{
	char	**cmd;
	char	*absolute_path;

	cmd = ft_split(p_argv, ' ');
	absolute_path = recup_the_bin_path(cmd[0], p_envp);
	perror("TESTEXEC\n");
	if (execve(absolute_path, cmd, p_envp) == -1)
	{
		// ft_printf("TEST\n");
		clear_char_tab(cmd);
		free(absolute_path);
		return (-1);
	}
	return (0);
}


int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	fork_pid;
	int	waitpid_status;
	int	pipefd[2]; //fd[0] = read | fd[1] = write
	int	filesfd[2]; //fd[0] = infile | fd[1] = outfile

	// If outfile not exist, open with O_CREAT flag
	filesfd[0] = open(argv[1], O_RDONLY);
	filesfd[1] = open(argv[(argc - 1)], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
	ft_printf("FD0 = %d, FD1 = %d, \n", filesfd[0], filesfd[1]);
	if (filesfd[0] == -1)
		i = 3;
	else
		i = 2;
	pipe(pipefd);
	while (i < (argc - 1))
	{
		if (i == 2) // Premier iteration le input doit etre rediriger vers le fichier intest ouvert plustot
			dup2(filesfd[0], 0);
		else
			dup2(pipefd[READ_ENDPIPE], 0);
		fork_pid = fork();
		if (fork_pid == 0) //Child process
		{
			if (i == (argc - 2)) // Derniere iteration le WRITE_ENDPIPE doit etre rediriger vers le fichier outtest ouvert plustot
			{
				perror("TEST 1\n");
				dup2(filesfd[1], 1);
			}
			else
			{
				perror("TEST 2\n");
				dup2(pipefd[WRITE_ENDPIPE], 1);
			}
			if (execution(argv[i], envp) == -1)
			{
				perror("Exec probleme\n");
				exit(2);
			}
		}
		waitpid(-1, &waitpid_status, 0);
		i++;
		perror("WHILE LOOP PASS : \n");
	}
	close(pipefd[WRITE_ENDPIPE]);
	close(pipefd[READ_ENDPIPE]);
	close(filesfd[0]);
	close(filesfd[1]);
	return (0);
}
