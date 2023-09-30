#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		all_len;
	char	*res;

	all_len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (all_len + 1));
	if (res == 0)
		error("malloc failed\n", NULL, 1);
	i = 0;
	while (s1 != NULL && *s1)
		res[i++] = *(s1++);
	while (s2 != NULL && *s2)
		res[i++] = *(s2++);
	res[i] = '\0';
	return (res);
}

int	str_check_space(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			return (1);
	}
	return (0);
}

int	find_index(char *str, char c)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (1);
}