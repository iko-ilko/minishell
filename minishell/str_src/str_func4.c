/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_func4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:53:53 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/01 15:53:53 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtok(char *str, char sepa)
{
	char	*stock;
	char	*p;

	if (str != NULL)
		stock = str;
	if (stock == NULL || *stock == '\0')
		return (NULL);
	p = stock;
	while (*stock != sepa && *stock != '\0')
		stock++;
	if (*stock == sepa)
	{
		*stock = '\0';
		stock++;
	}
	else
		stock = NULL;
	return (p);
}

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

char	*ft_itoa(int nbr)
{
	char	*result;
	int		n;
	int		len;

	len = 0;
	if (nbr == 0)
		len++;
	n = nbr;
	while (n)
	{
		n /= 10;
		len++;
	}
	result = ft_calloc(len + 1, sizeof(char));
	if (nbr == 0)
	{
		result[0] = '0';
		return (result);
	}
	while (nbr)
	{
		result[--len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (result);
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dst_len + 1 > dstsize)
		return (src_len + dstsize);
	i = 0;
	while (dst_len + i < dstsize - 1 && src[i])
	{
			dst[dst_len + i] = src[i];
			i++;
	}
	dst[dst_len + i] = '\0';
	return (src_len + dst_len);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	int		i;
	char	*res;

	if (len == 0)
	{
		res = malloc(sizeof(char));
		*res = 0;
		return (res);
	}
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == 0)
		return (0);
	i = 0;
	if (start < (unsigned int)ft_strlen(s))
	{
		while (len--)
			res[i++] = s[start++];
	}
	res[i] = '\0';
	return (res);
}
