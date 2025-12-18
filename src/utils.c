/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:38:39 by akolupae          #+#    #+#             */
/*   Updated: 2025/12/16 12:56:37 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time_millisec(void)
{
	struct timeval	time;
	int				millisec;

	if (gettimeofday(&time, NULL) == FAILURE)
		return (FAILURE);
	millisec = (int) time.tv_sec * 1000 + (int) time.tv_usec / 1000;
	return (millisec);
}

void	set_value(pthread_mutex_t *mutex, bool *var, bool value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

void	release_forks(t_philo *philo)
{
	set_value(&philo->fork[0]->take_fork, &philo->fork[0]->avail, true);
	set_value(&philo->fork[1]->take_fork, &philo->fork[1]->avail, true);
}

bool	print_message(t_philo philo, char *msg)
{
	int	time;
	int	cur_time;

	if (philo.args->finish)
		return (false);
	pthread_mutex_lock(&philo.args->print);
	cur_time = get_time_millisec();
	if (cur_time == FAILURE)
	{
		pthread_mutex_unlock(&philo.args->print);
		return (false);
	}
	time = cur_time - philo.args->start_time;
	if (printf("%d %d %s", time, philo.index, msg) == FAILURE)
	{
		pthread_mutex_unlock(&philo.args->print);
		return (false);
	}
	pthread_mutex_unlock(&philo.args->print);
	return (true);
}
