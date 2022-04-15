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

void	clear_char_tab(char **tab, int size);
char	**recup_the_good_bin_path(char **p_envp, char *binary_name);

#endif
