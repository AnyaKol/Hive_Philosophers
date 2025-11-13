/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:17:49 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/13 15:48:06 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_numbers(int argc, char **argv);
static bool	str_is_number(char *args);
static bool	int_overflow(char *str);

bool	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd(ARGNUM, STDERR_FILENO);
		return (false);
	}
	if (!check_numbers(argc - 1, &argv[1]))
		return (false);
	return (true);
}

static bool	check_numbers(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc && argv[i])
	{
		if (!str_is_number(argv[i]) || !int_overflow(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	str_is_number(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] < '0' || args[i] > '9')
		{
			ft_putendl_fd(NOTNUM, STDERR_FILENO);
			return (false);
		}
		i++;
	}
	if (args[0] && args[0] == '0')
	{
		ft_putendl_fd(WFORMAT, STDERR_FILENO);
		return (false);
	}
	return (true);
}

static bool	int_overflow(char *str)
{
	int num;

	num = ft_atoi(str);
	if (num == 0 && str[0] != '0')
	{
		ft_putendl_fd(OVERFLOW, STDERR_FILENO);
		return (false);
	}
	return (true);
}
