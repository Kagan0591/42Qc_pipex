int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
	{
		ft_printf("\n");
		return (1);
	}
	return (0);
}
