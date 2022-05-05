#ifndef PIPEX_H
# define PIPEX_H

# define READ_ENDPIPE 0
# define WRITE_ENDPIPE 1
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"
# include "doubly_linked_list.h"
# include <stdio.h>

// typedef struct t_pid_data
// {
// 	int	parent_pid;
// 	int	*childs_pid;

// }t_pid_data;

typedef struct t_data
{
	int			filesfd[2]; //fd[0] = infile | fd[1] = outfile
	int			pipefd[2]; //fd[0] = read | fd[1] = write
	int			mainloop_i;
	int			*child_pid;
	t_cmdinfos	*cmds_list;
}t_data;

t_data	*mem_init(void);
void	clear_char_tab(char **tab);
int		open_files(t_data *p_fd_data, int argc, char **p_argv);
int		ft_execve(char *p_argv, char **p_envp);
void	setup_io_child_proc_1(t_data *prog_data, int argc);


#endif
