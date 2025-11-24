/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:38:25 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/24 16:38:29 by akolupae         ###   ########.fr       */
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
	if (data->forks)
	{
		destroy_mutex(data);
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
		if (pthread_mutex_destroy(&data->forks[i].take_fork) != SUCCESS)
		{
			perror("pthread_mutex_destroy");
			return ;
		}
		i++;
	}
	if (pthread_mutex_destroy(&data->args.finish_lock) != SUCCESS
		|| pthread_mutex_destroy(&data->args.print) != SUCCESS)
		{
			perror("pthread_mutex_destroy");
			return ;
		}
}
