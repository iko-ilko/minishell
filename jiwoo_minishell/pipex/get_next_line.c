/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:53:01 by ilko              #+#    #+#             */
/*   Updated: 2023/09/24 20:14:42 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	*if_error_gnl(t_node *backup)
{
	free(backup->str);
	backup->str = NULL;
	backup->len = 0;
	return (NULL);
}

static void	cat_backup(t_node *backup, char *buf, int rd_size)
{
	int		i;
	int		j;
	char	*temp;

	while (backup->len > 0 && *(backup->str + backup->len))
		backup->len++;
	temp = malloc(sizeof(char) * (backup->len + rd_size + 1));
	if (temp == NULL)
		return ;
	i = -1;
	while (++i < backup->len)
		*(temp + i) = *(backup->str + i);
	j = -1;
	while (++j < rd_size)
		*(temp + i + j) = *(buf + j);
	*(temp + i + j) = '\0';
	free(backup->str);
	backup->str = temp;
	backup->len = i + j;
}

static int	check_nl(t_node *backup, char **res)
{
	int		i;
	char	*temp;

	i = -1;
	while (backup->len != 0 && *(backup->str + ++i))
	{
		if (*(backup->str + i) == '\n')
		{
			*res = ft_strndup(backup->str, i + 1);
			if (*res == NULL)
				return ((long)if_error_gnl(backup));
			temp = ft_strndup(backup->str + i + 1, backup->len - i - 1);
			if (temp == NULL)
			{
				free(*res);
				*res = if_error_gnl(backup);
				return (0);
			}
			free(backup->str);
			backup->str = temp;
			backup->len = backup->len - i - 1;
			return (0);
		}
	}
	return (1);
}

static int	if_rd_size_is_zero_less(t_node *backup, int rd_size, char **res)
{
	if (rd_size < 0)
		return (-1);
	if (rd_size == 0)
	{
		if (backup->len == 0)
			return (-1);
		*res = ft_strndup(backup->str, backup->len);
		if (*res == NULL)
			return (-1);
		backup->len -= backup->len;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_node	backup;
	char			buf[BUFFER_SIZE + 1];
	char			*res;
	int				rd_size;

	res = 0;
	if (!check_nl(&backup, &res))
		return (res);
	rd_size = 1;
	while (rd_size)
	{
		rd_size = read(fd, buf, BUFFER_SIZE);
		if (if_rd_size_is_zero_less(&backup, rd_size, &res) == -1)
			return (if_error_gnl(&backup));
		buf[BUFFER_SIZE] = '\0';
		cat_backup(&backup, buf, rd_size);
		if (!check_nl(&backup, &res))
			return (res);
	}
	return (res);
}
