#include "../minishell.h"

int	ft_strlen(char *str)
{
	int	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*(s1++) != *(s2++))
			return (0);
	}
	return (1);
}

char	*ft_strdup(char *s1)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(s1);
	res = malloc(sizeof(char) * (len + 1));
	if (res == 0)
		error("malloc failed\n", NULL, 1);
	i = -1;
	while (++i < len)
		res[i] = s1[i];
	res[i] = 0;
	return (res);
}

char	*ft_strndup(char *s1, int len)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		error("malloc failed\n", NULL, 1);
	i = 0;
	while (i < len)
	{
		*(res + i) = *(s1 + i);
		i++;
	}
	*(res + i) = '\0';
	return (res);
}