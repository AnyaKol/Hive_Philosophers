/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:33:41 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/21 13:20:34 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_mutex(t_data *data);
static bool	init_one_philo(t_data *data, int index);

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
		i += 2;
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
	return (true);
}

static bool	init_one_philo(t_data *data, int index)
{
	int		result;
	t_philo	*philo;
	
	philo = malloc(1 * sizeof(t_philo));
	if (!philo)
		return (false);
	philo->index = index + 1;
	philo->last_meal = data->args.start_time;
	philo->args = &data->args;
	philo->fork[0] = &data->forks[index];
	if (index == data->philos_num - 1)
		philo->fork[1] = &data->forks[0];
	else
		philo->fork[1] = &data->forks[index + 1];
	result = pthread_create(&data->philos[index], NULL, routine, philo);
	if (result == FAILURE)
	{
		perror("pthread_create");
		return (false);
	}
	return (true);
}
