/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:17:49 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/25 19:07:22 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	check_numbers(int argnum, char **argv, int *numbers);
static bool	str_is_number(char *str);
static bool	int_overflow(int num, char *str);

bool	check_args(int argc, char **argv, t_data *data)
{
	int	numbers[5];

	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd(ARGNUM, STDERR_FILENO);
		return (false);
	}
	if (!check_numbers(argc - 1, &argv[1], &numbers[0]))
		return (false);
	data->philos_num = numbers[0];
	data->args.time_to_die = numbers[1];
	data->args.time_to_eat = numbers[2];
	data->args.time_to_sleep = numbers[3];
	data->args.food_num = numbers[4];
	data->args.can_take = (data->philos_num / 2 > 0);
	data->args.start_time = get_time_millisec();
	return (true);
}

static bool	check_numbers(int argnum, char **argv, int *numbers)
{
	int	i;

	if (!*argv)
		return (true);
	numbers[4] = -1;
	i = 0;
	while (i < argnum && argv[i])
	{
		numbers[i] = ft_atoi(argv[i]);
		if (!str_is_number(argv[i]) || !int_overflow(numbers[i], argv[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	str_is_number(char *str)
{
	int	i;

	if (!*str)
		return (true);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit((int) str[i]))
		{
			ft_putendl_fd(NOTNUM, STDERR_FILENO);
			return (false);
		}
		i++;
	}
	if (str[0] == '0' && str[1] != '\0')
	{
		ft_putendl_fd(WFORMAT, STDERR_FILENO);
		return (false);
	}
	return (true);
}

static bool	int_overflow(int num, char *str)
{
	if (!*str)
		return (true);
	if (num == 0 && !(str[0] == '0' && str[1] == '\0'))
	{
		ft_putendl_fd(OVERFLOW, STDERR_FILENO);
		return (false);
	}
	else if (num == 0)
	{
		ft_putendl_fd(ARGZERO, STDERR_FILENO);
		return (false);
	}
	return (true);
}
