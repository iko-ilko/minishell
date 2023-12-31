/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_func5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwkim2 <jiwkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:53:49 by jiwkim2           #+#    #+#             */
/*   Updated: 2023/12/01 15:53:49 by jiwkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(char *str)
{
	int	result;
	int	sign;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
		sign = 44 - *str++;
	result = 0;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + *(str++) - '0';
	return (result * sign);
}

unsigned char	ft_atous_util(int *error)
{
	*error = FAIL;
	return (255);
}

unsigned char	ft_atous_minishell(char *str, int *error)
{
	unsigned char	result;
	long long		temp;
	int				sign;

	if (str == NULL)
		return (0);
	if (str[0] == '\0')
		return (ft_atous_util(error));
	sign = 1;
	if (*str == '-' || *str == '+')
		sign = 44 - *str++;
	temp = 0;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (ft_atous_util(error));
		temp = temp * 10 + *(str++) - '0';
		if (temp < 0)
			return (ft_atous_util(error));
	}
	*error = SUCCESS;
	result = temp * sign;
	return (result);
}

int	check_args_in_execute(char **args)
{
	int		i;
	char	*temp;

	i = 0;
	while (args[i])
	{
		temp = ft_strtrim(args[i], " ");
		if (temp[0] != '\0')
		{
			free_single((void **)&temp);
			return (i);
		}
		i++;
		free_single((void **)&temp);
	}
	return (-1);
}
