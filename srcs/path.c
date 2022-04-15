
#include "pipex.h"
static char	*path_env_var_to_str(char **p_envp)
{
	int		i;

	i = 0;
	if (p_envp)
	{
		while (p_envp[i] != NULL)
		{
			if (strncmp(p_envp[i], "PATH=", 5) == 0)
				return (p_envp[i]);
			i++;
		}
	}
	return (NULL);
}

// char	*find_the_good_path()

char	**recup_the_good_bin_path(char **p_envp, char *binary_name)
{
	char	*path_env_var;
	char	**splitted_path;
	char	*trimmed_path;
	(void) binary_name;

	path_env_var = path_env_var_to_str(p_envp);
	trimmed_path = ft_strtrim(path_env_var, "PATH=");
	ft_printf("%s\n", trimmed_path);
	splitted_path = ft_split(trimmed_path, ':');
	ft_printf("%d\n", ft_strofstrlen(splitted_path));
	clear_char_tab(splitted_path, ft_strofstrlen(splitted_path));
	free((void*)trimmed_path);
	return (NULL);

}

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)	argc;
// 	(void)	argv;
// 	// char	*str;

// 	recup_the_good_bin_path(envp, "echo");
// 	//ft_printf("%s\n", str);
// 	return (0);
// }
