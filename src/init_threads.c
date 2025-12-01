/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:33:41 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/24 20:03:02 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool		init_one_philo(t_data *data, int index);
static t_philo	*init_philo_struct(t_data *data, int index);
static void		swap_forks(t_fork **ptr1, t_fork **ptr2);
static void		wait_for_philos(t_data *data);

bool	init_threads(t_data *data)
{
	int		i;

	i = 1;
	while (i < data->philos_num)
	{
		if (!init_one_philo(data, i))
			return (false);
		i += 2;
	}
	wait_for_philos(data);
	i = 0;
	while (i < data->philos_num)
	{
		if (!init_one_philo(data, i))
			return (false);
		i += 2;
	}
	return (true);
}

static void	wait_for_philos(t_data *data)
{
	if (data->philos_num < 2)
		return ;
	while (data->forks[1].avail)
	{
		if (get_time_millisec() - data->args.start_time > TIMEOUT)
			return ;
	}
}

static bool	init_one_philo(t_data *data, int index)
{
	int		result;
	t_philo	*philo;

	philo = init_philo_struct(data, index);
	if (!philo)
		return (false);
	result = pthread_create(&data->philos[index], NULL, routine, philo);
	if (result == FAILURE)
	{
		perror("pthread_create");
		return (false);
	}
	return (true);
}

static t_philo	*init_philo_struct(t_data *data, int index)
{
	t_philo	*philo;

	philo = malloc(1 * sizeof(t_philo));
	if (!philo)
	{
		perror("malloc");
		return (false);
	}
	philo->index = index + 1;
	philo->last_meal = get_time_millisec();
	philo->args = &data->args;
	philo->fork[0] = &data->forks[index];
	if (index == data->philos_num - 1)
		philo->fork[1] = &data->forks[0];
	else
		philo->fork[1] = &data->forks[index + 1];
	if (index / 2 == 1)
		swap_forks(&philo->fork[0], &philo->fork[1]);
	return (philo);
}

static void	swap_forks(t_fork **ptr1, t_fork **ptr2)
{
	t_fork	*temp;

	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}
