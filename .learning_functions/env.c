#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	(void)	argc;
	(void)	argv;
	int		i;

	i = 0;
	while (**envp)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
