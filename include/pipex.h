#ifndef PIPEX_H
# define PIPEX_H
# define READ_ENDPIPE 0
# define WRITE_ENDPIPE 1

# include <unistd.h>
//# include <stdlib.h>
# include <errno.h>
//# include <sys/stat.h>
//# include <sys/time.h>
//# include <sys/types.h>
# include <sys/wait.h>
//# include <fcntl.h>
# include <stdio.h>
# include "libft.h"
# include "doubly_linked_list.h"

typedef struct t_data
{
	int			filesfd[2];
	int			infile_flag;
	int			pipefd[2];
	int			here_doc_flag;
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
char	*get_next_line(int fd);


#endif
