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

typedef struct t_data
{
	int			filesfd[2]; //fd[0] = infile | fd[1] = outfile
	int			pipefd[2]; //fd[0] = read | fd[1] = write
	int			mainloop_i;
	int			here_doc_flag; // if == 1, here_doc are present
	int			here_doc_pipefd[2];
	t_cmdinfos	*cmds_list;
}t_data;

t_data	struct_mem_init();
void	clear_char_tab(char **tab);
int		open_files(t_data *p_fd_data, int argc, char **p_argv);
int		cmd_parsing(t_cmdinfos_data *exec_data, char *p_argv, char **envp);
int		execution_time(t_data *prog_data, char **envp);
void	setup_input(t_data *prog_data);
void	setup_output(t_data *prog_data);
int	here_doc(t_data *prog_data, char *limiter);
char	*get_next_line(int fd);


#endif
