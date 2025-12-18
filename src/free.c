/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:38:25 by akolupae          #+#    #+#             */
/*   Updated: 2025/12/16 12:48:59 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutex(t_data *data);

void	free_data(t_data *data)
{
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	destroy_mutex(data);
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
}

static void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		pthread_mutex_destroy(&data->forks[i].take_fork);
		i++;
	}
	pthread_mutex_destroy(&data->args.finish_lock);
	pthread_mutex_destroy(&data->args.print);
}
