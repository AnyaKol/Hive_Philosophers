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

bool	init_threads(t_data *data)
{
	int		i;
	int		result;
	t_philo	*philo;

	data->philos = malloc(data->philos_num * sizeof(pthread_t));
	if (!data->philos)
		return (false);
	data->forks = malloc(data->philos_num * sizeof(t_fork));
	if (!data->forks)
	{
		free(data->philos);
		return (false);
	}
	i = 0;
	while (i < data->philos_num)
	{
		philo = malloc(1 * sizeof(t_philo));
		if (!philo)
		{
			free(data->philos);
			free(data->forks);
			return (false);
		}
		philo->args = &data->args;
		philo->fork[0] = &data->forks[i];
		if (i == data->philos_num - 1)
			philo->fork[1] = &data->forks[0];
		else
			philo->fork[1] = &data->forks[i + 1];
		resullt = pthread_create(data->philos[i], NULL, routine, philo);
		i++;
	}
	return (true);
}
