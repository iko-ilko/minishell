/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:12:38 by ilko              #+#    #+#             */
/*   Updated: 2023/09/24 20:12:38 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	if (n == 0 || !s1 || !s2)
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
