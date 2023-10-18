#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		all_len;
	char	*res;

	all_len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (all_len + 1));
	if (res == 0)
		exit_error("malloc failed\n", NULL, 1);
	i = 0;
	while (s1 != NULL && *s1)
		res[i++] = *(s1++);
	while (s2 != NULL && *s2)
		res[i++] = *(s2++);
	res[i] = '\0';
	return (res);
}

// int	str_check_space(char *str)
// {
// 	int	i;

// 	if (str == NULL)
// 		return (0);
// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] == ' ')
// 			return (1);
// 	}
// 	return (0);
// }
// cat $USER \f | cat
char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	char	*res;

	start = 0;
	if (s1 == 0 || set == 0)
		return (0);
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
			start++;
	while (end > 0 && s1[end - 1] && ft_strchr(set, s1[end - 1]))
			end--;
	if (start > end)
		return (ft_strdup(""));
	res = ft_substr(s1, start, end - start);
	return (res);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;
	size_t	i;

	i = 0;
	p = (char *)malloc(size * count);
	if (p == NULL)
		exit_error("malloc failed\n", NULL, 1);
	while (i < size * count)
	{
		p[i] = 0;
		i++;
	}
	return ((void *)p);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int		i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && i < n - 1)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
