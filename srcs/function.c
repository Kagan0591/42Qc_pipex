#include "libft.h"

char	*ft_strchr_pattern(const char *s, char *str, int delemiter)
{
	char	*start_of_str;
	char	*ret_pattern;
	int		i;
	int		j;

	i = 0;
	j = 0;
	start_of_str = str;
	while (s[i] || s[i] == delemiter)
	{
		while (s[i] == str[j])
		{
			i++;
			j++;
			if (s[i] == delemiter)
			{
				ret_pattern = malloc(sizeof(char) * i);
				ft_strlcpy(s, ret_pattern, i);
				free (s);
			}
		}
		j = 0;
		i++;

	}
	return (0);
}

char	*recup_the_bin_path(char **p_envp)
{
	char	*path;


	while (ft_strchr_pattern() != -1)
	{
		//GNL pour sortir chaque lignes
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)	argc;
	(void)	argv;



}
