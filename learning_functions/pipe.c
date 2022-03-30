#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// int	main(void)
// {
// 	//fd[0] = read
// 	//fd[1] = write
// 	int fd[2];
// 	int id;
// 	int	a;
// 	int	b;

// 	if (pipe(fd) == -1)
// 	{
// 		printf("An error occured during the pipe\n");
// 		return (0);
// 	}
// 	id = fork();
// 	if (id == -1)
// 	{
// 		printf("An error occured with the fork\n");
// 		return (1);
// 	}
// 	if (id == 0)
// 	{
// 		close(fd[0]);
// 		printf("input a number\n");
// 		scanf("%d", &a);
// 		if (write(fd[1], &a, sizeof(int)) == -1)
// 		{
// 			printf("An error occured when writing to the pipe\n");
// 			close(fd[1]);
// 			return (2);
// 		}
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		if (read(fd[0], &b, sizeof(int)) == -1)
// 		{
// 			printf("An error occured when writing to the pipe\n");
// 			close(fd[0]);
// 			return (3);
// 		}
// 		printf("Number got from child process: %d\n", b);
// 		close(fd[0]);
// 	}
// 	return (1);
// }

// int	main(void)
// {
// 	int	array[] = {1, 2, 3, 4, 1, 2};
// 	int	array_size;

// 	array_size = sizeof(array) / sizeof(int);
// 	printf("The size of the array is: %d", array_size);
// 	return (0);
// }

int	main(void)
{
	int	array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int	array_size;
	int	pid;
	int	fd[2];
	int	start, end;
	int	i;
	int	sum;
	int	total_sum;
	int	sum_from_children;
	/* La fonction pipe qui créer le lien entre les deux fd et assure
	 *la transmission des données. */
	if (pipe(fd) == -1)
	{
		printf("Pipe probleme !\n");
		return (1);
	}
	array_size = sizeof(array) / sizeof(int);
	/* LA fonction fork qui créer un nouveau processus depuis
	 * celui en cour d'execution en y copiant les variables bien sur. */
	pid = fork();
	if (pid == -1)
	{
		printf("Fork probleme !\n");
		return (2);
	}

	if (pid == 0) // Take the partial sum from the child part (start var to size / 2)
	{
		start = 0;
		end = array_size / 2;
	}
	else // Take the partial sum form parent process (size / 2 to end var)
	{
		start = array_size / 2;
		end = array_size;
	}
	/* Calculate the partial sum. */
	i = start;
	sum = 0;
	while (i < end)
	{
		sum += array[i];
		i++;
	}
	/* Send the sum value to pipe fd[1]. */
	sum_from_children = 0;
	if (pid == 0)
	{
		close(fd[0]);
		if (write(fd[1], &sum, sizeof(sum)) == -1)
			return (3);
		close(fd[1]);
	}
	/* Receive the sum form pipe fd[0] from the children and put it into
	 * sum_from_children variable. */
	else
	{
		close(fd[1]);
		if (read(fd[0], &sum_from_children, sizeof(sum_from_children)) == -1)
			return (4);
		close(fd[0]);
		wait(NULL);
	}
	/* calculate the sum of all numbers */
	if (pid == 0)
		return(0);
	total_sum = sum + sum_from_children;
	printf("La somme total des nombre est: %d", total_sum);
	return (0);
}
