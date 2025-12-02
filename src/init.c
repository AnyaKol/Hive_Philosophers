/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:33:41 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/24 19:28:01 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_mutex(t_data *data);

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
