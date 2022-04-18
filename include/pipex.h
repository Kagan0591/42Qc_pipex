#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"
# include <stdio.h>

typedef struct		t_exec
{
	char			*bin_path;
	char			**bin_arguments;
	struct d_exec	*next;
	struct d_exec	*previous;
}					t_exec;

void	clear_char_tab(char **tab, int size);
char	*recup_the_bin_path(char *bin_name, char **p_envp);
int	fill_in_exec_struct(char *bin_n_option, t_exec *cmd_datastruct, char **p_envp)

#endif
