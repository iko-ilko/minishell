/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_func1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:54:00 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/01 15:54:01 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_strlcpy(char *dst, char *src, int dstsize)
{
	int	i;
	int	src_len;

	src_len = 0;
	while (*(src + src_len))
		src_len++;
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (*(src + i) && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

static char	**my_free(char **res, int cnt_idx)
{
	while (cnt_idx >= 0)
		free(res[cnt_idx--]);
	free(res);
	return (NULL);
}

static char	**make_wdspace(char *s, char c, int *wdcnt)
{
	char	**res;

	*wdcnt = 0;
	while (*s)
	{
		if (*s != c)
		{
			(*wdcnt)++;
			while (*s != c && *s)
				s++;
			continue ;
		}
		s++;
	}
	res = malloc(sizeof(char *) * (*wdcnt + 1));
	return (res);
}

static char	**make_chspace(char *s, char c, char **res)
{
	int	ch_len;
	int	wd_idx;

	wd_idx = 0;
	while (*s)
	{
		ch_len = 0;
		if (*s != c)
		{
			while (*(s + ch_len) != c && *(s + ch_len))
				ch_len++;
			res[wd_idx] = malloc(sizeof(char) * (ch_len + 1));
			if (res[wd_idx] == 0)
				return (my_free(res, wd_idx - 1));
			ft_strlcpy(res[wd_idx++], s, ch_len + 1);
			s += ch_len;
			continue ;
		}
		s++;
	}
	res[wd_idx] = 0;
	return (res);
}

char	**ft_split(char *s, char c)
{
	char	**res;
	int		wdcnt;

	if (s == NULL)
		return (NULL);
	while (*s && *s == c)
		s++;
	res = make_wdspace(s, c, &wdcnt);
	if (res == 0)
		exit_error("malloc failed\n", NULL, 1);
	res = make_chspace(s, c, res);
	if (res == 0)
		exit_error("malloc failed\n", NULL, 1);
	return (res);
}
