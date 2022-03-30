#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/time.h>

int	main(void)
{
	int	fd;
	int	x;

	x = 97;
	if (mkfifo("fifofile", 0777) == -1)
	{
		if (errno != EEXIST)
		{
			printf("fifofile already exist\n");
			return (1);
		}
	}
	printf("Opening...\n");
	fd = open("fifofile", O_WRONLY);
	printf("Opened\n");
	if (write(fd, &x, 1) == -1)
		return (2);
	printf("\n\n");
	close(fd);
	return (0);
}