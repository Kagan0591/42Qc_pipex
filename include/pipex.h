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
	int			mainloop_i;
	t_cmdinfos	*cmds_list;
}t_data;

t_data	*struct_mem_init(int argc);
void	clear_char_tab(char **tab);
int		open_files(t_data *p_fd_data, int argc, char **p_argv);
int		cmd_parsing(t_cmdinfos_data *exec_data, char *p_argv, char **envp);
int		execution_time(t_cmdinfos_data *exec_data, char **envp);
void	setup_io(t_data *prog_data, int argc);


#endif
