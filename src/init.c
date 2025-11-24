/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:33:41 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/24 18:58:53 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_mutex(t_data *data);
static bool	init_one_philo(t_data *data, int index);
static void	swap_forks(t_fork **ptr1, t_fork **ptr2);
static bool	check_timeout(t_args args);

bool	init_data(t_data *data)
{
	data->philos = malloc(data->philos_num * sizeof(pthread_t));
	data->forks = malloc(data->philos_num * sizeof(t_fork));
	if (!data->philos || !data->forks || !init_mutex(data))
	{
		free_data(data);
		return (false);
	}
	return (true);
}

static bool	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_mutex_init(&data->forks[i].take_fork, NULL) != SUCCESS)
		{
			perror("pthread_mutex_init");
			return (false);
		}
		data->forks[i].avail = true;
		i++;
	}
	if (pthread_mutex_init(&data->args.finish_lock, NULL) != SUCCESS
		|| pthread_mutex_init(&data->args.print, NULL) != SUCCESS)
		{
			perror("pthread_mutex_init");
			return (false);
		}
	data->args.finish = false;
	return (true);
}

bool	init_threads(t_data *data)
{
	int		i;

	i = 1;
	while (i < data->philos_num)
	{
		if (!init_one_philo(data, i))
		{
			free_data(data);
			return (false);
		}
		/*
		while (data->forks[i].avail)
		{
			if (!check_timeout(data->args))
			{
				printf("Timeout\n");
				return (false);
			}
		}
		*/
		i += 2;
	}
	if (data->philos_num > 1)
	{
		while (data->forks[1].avail)
		{
			if (!check_timeout(data->args))
			{
				printf("Timeout\n");
				return (false);
			}
		}
	}
	i = 0;
	while (i < data->philos_num)
	{
		if (!init_one_philo(data, i))
		{
			free_data(data);
			return (false);
		}
		i += 2;
	}
	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_join(data->philos[i], NULL) != SUCCESS)
		{
			perror("pthread_join");
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	init_one_philo(t_data *data, int index)
{
	int		result;
	t_philo	*philo;
	
	philo = malloc(1 * sizeof(t_philo));
	if (!philo)
	{
		perror("malloc");
		return (false);
	}
	philo->index = index + 1;
	philo->last_meal = data->args.start_time;
	philo->args = &data->args;
	philo->fork[0] = &data->forks[index];
	if (index == data->philos_num - 1)
		philo->fork[1] = &data->forks[0];
	else
		philo->fork[1] = &data->forks[index + 1];
	if (index / 2 == 1)
		swap_forks(&philo->fork[0], &philo->fork[1]);
	result = pthread_create(&data->philos[index], NULL, routine, philo);
	if (result == FAILURE)
	{
		perror("pthread_create");
		return (false);
	}
	return (true);
}

static void	swap_forks(t_fork **ptr1, t_fork **ptr2)
{
	t_fork *temp;

	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

static bool	check_timeout(t_args args)
{
	if (get_time_millisec() - args.start_time > args.time_to_die)
		return (false);
	return (true);
}
