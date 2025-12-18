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

bool	check_death(int cur_time, t_philo philo)
{
	int	time_passed;

	time_passed = cur_time - philo.last_meal;
	if (time_passed >= philo.args->time_to_die)
		return (false);
	return (true);
}

bool	check_eat_count(t_philo *philo)
{
	bool	result;

	result = true;
	if (philo->eat_count == philo->args->food_num)
	{
		pthread_mutex_lock(&philo->args->left_philos_lock);
		philo->args->left_philos--;
		if (philo->args->left_philos == 0)
			result = false;
		pthread_mutex_unlock(&philo->args->left_philos_lock);
	}
	return (result);
}
