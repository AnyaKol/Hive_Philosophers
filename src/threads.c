/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:33:41 by akolupae          #+#    #+#             */
/*   Updated: 2025/12/16 12:54:46 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		init_threads(t_data *data);
static bool		init_one_philo(t_data *data, int index);
static t_philo	*init_philo_struct(t_data *data, int index);

bool	init_and_join_threads(t_data *data)
{
	int		i;
	int		num;
	bool	result;

	i = 0;
	num = init_threads(data);
	result = (num == data->philos_num);
	data->args.start_time = get_time_millisec();
	data->args.start = true;
	while (i < num)
	{
		if (pthread_join(data->philos[i], NULL) != SUCCESS)
			result = false;
		i++;
	}
	return (result);
}

static int	init_threads(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philos_num)
	{
		if (!init_one_philo(data, i))
			break ;
		i++;
	}
	return (i);
}

static bool	init_one_philo(t_data *data, int index)
{
	t_philo	*philo;

	philo = init_philo_struct(data, index);
	if (!philo)
		return (false);
	if (pthread_create(&data->philos[index], NULL, routine, philo) == FAILURE)
	{
		free(philo);
		return (false);
	}
	return (true);
}

static t_philo	*init_philo_struct(t_data *data, int index)
{
	t_philo	*philo;

	philo = malloc(1 * sizeof(t_philo));
	if (!philo)
		return (false);
	philo->index = index + 1;
	philo->eat_count = 0;
	philo->last_status = START;
	philo->args = &data->args;
	philo->fork[0] = &data->forks[index];
	if (index == data->philos_num - 1)
		philo->fork[1] = &data->forks[0];
	else
		philo->fork[1] = &data->forks[index + 1];
	return (philo);
}
