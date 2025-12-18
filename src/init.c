/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:33:41 by akolupae          #+#    #+#             */
/*   Updated: 2025/12/16 12:49:30 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_mutex(t_data *data);
static bool	init_mutex_forks(t_data *data);

bool	init_data(t_data *data)
{
	data->philos = malloc(data->philos_num * sizeof(pthread_t));
	data->forks = malloc(data->philos_num * sizeof(t_fork));
	if (!data->philos || !data->forks || !init_mutex(data))
	{
		if (data->philos)
			free(data->philos);
		if (data->forks)
			free(data->forks);
		return (false);
	}
	return (true);
}

static bool	init_mutex(t_data *data)
{
	int	init[3];

	init[0] = pthread_mutex_init(&data->args.finish_lock, NULL);
	init[1] = pthread_mutex_init(&data->args.print, NULL);
	init[2] = pthread_mutex_init(&data->args.left_philos_lock, NULL);
	if (init[0] != SUCCESS || init[1] != SUCCESS || init[2] != SUCCESS
		|| !init_mutex_forks(data))
	{
		if (init[0] == SUCCESS)
			pthread_mutex_destroy(&data->args.finish_lock);
		if (init[1] == SUCCESS)
			pthread_mutex_destroy(&data->args.print);
		if (init[2] == SUCCESS)
			pthread_mutex_destroy(&data->args.left_philos_lock);
		return (false);
	}
	return (true);
}

static bool	init_mutex_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_mutex_init(&data->forks[i].take_fork, NULL) != SUCCESS)
		{
			while (i > 0)
				pthread_mutex_destroy(&data->forks[--i].take_fork);
			return (false);
		}
		data->forks[i].avail = true;
		i++;
	}
	return (true);
}
