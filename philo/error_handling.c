/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoster <mkoster@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:34:14 by mkoster           #+#    #+#             */
/*   Updated: 2024/07/30 16:07:45 by mkoster          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *s)
{
	write(2, s, ft_strlen(s));
}

int	check_for_errors(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		print_error(ERROR_ARG_MESSAGE);
		return (1);
	}
	else
	{
		if (!check_num(argv, argc))
		{
			print_error(ERROR_NAN_MESSAGE);
			return (2);
		}
		if (!check_integer(argv, argc))
		{
			print_error(ERROR_INT_MESSAGE);
			return (3);
		}
	}
	return (0);
}

int	check_num(char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_integer(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_atoi_error(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi_error(char *nptr)
{
	double	sign;
	double	result;
	int		i;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || (nptr[i] == ' '))
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		result = result * 10 + (nptr[i++] - '0');
	result = result * sign;
	if (result > 2147483647 || result < -2147483648)
		return (0);
	else
		return (1);
}
