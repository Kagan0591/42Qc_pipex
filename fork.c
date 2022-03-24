#include <stdio.h>
#include <unistd.h>

// int	main(void)
// {

// 	fork();
// 	printf("Hello world\n");
// 	return (0);
// }

int	main(void)
{
	int	pid;
	int	i;
	int	n;

	i = 0;
	pid = fork();
	if (pid == 0)
		n = 1;
	else
		n = 6;
	for (i = n; i < n + 5; i++)
	{
		printf("%d ", i);
		fflush(stdout);
	}
	printf("\n");
	return (0);
}