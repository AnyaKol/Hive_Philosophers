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

	if (!*argv)
		return (true);
	i = 0;
	while (i < argc && argv[i])
	{
		if (!str_is_number(argv[i]) || !int_overflow(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	str_is_number(char *arg)
{
	int	i;

	if (!*arg)
		return (true);
	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			ft_putendl_fd(NOTNUM, STDERR_FILENO);
			return (false);
		}
		i++;
	}
	if (arg[0] == '0' && arg[1] != '\0')
	{
		ft_putendl_fd(WFORMAT, STDERR_FILENO);
		return (false);
	}
	return (true);
}

static bool	int_overflow(char *str)
{
	int num;

	if (!*str)
		return (true);
	num = ft_atoi(str);
	if (num == 0 && !(str[0] == '0' && str[1] == '\0'))
	{
		ft_putendl_fd(OVERFLOW, STDERR_FILENO);
		return (false);
	}
	return (true);
}
