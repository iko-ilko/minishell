/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:28:34 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/09/16 18:58:57 by jiwkim2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		i;
	int		len;

	if (s1 == 0)
		return (0);
	len = 0;
	while (s1[len])
		len++;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
// char	*ft_strcpy(char *dest, char *src)
// {
// 	int	i;

// 	i = 0;
// 	while (*(src + i) != '\0')
// 	{
// 		*(dest + i) = *(src + i);
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	while (*s)
// 	{
// 		if (*s == c)
// 			return ((char *)s);
// 		s++;
// 	}
// 	if (c == '\0')
// 		return ((char*)s);
// 	return (0);
// }

// void	*ft_calloc(size_t count, size_t size)
// {
// 	char	*p;
// 	size_t	i;

// 	i = 0;
// 	p = (char *)malloc(size * count);
// 	if (p == NULL)
// 		return (NULL);
// 	while (i < size * count)
// 	{
// 		p[i] = 0;
// 		i++;
// 	}
// 	return ((void *)p);
// }