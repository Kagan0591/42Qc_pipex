#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	int	fd;
	char	inject[] = {"Nouveau mot de passe"};
	if (access("file", W_OK) != 0)
		return (1);
	//
	//
	// The attack simulation
	symlink("./etc/passwd", "file");
	//
	//
	fd = open("passwd", O_WRONLY);
	write(fd, inject, sizeof(inject));
	return (0);
}