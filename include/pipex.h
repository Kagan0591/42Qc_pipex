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
# include <stdio.h>

void	clear_char_tab(char **tab);

#endif
