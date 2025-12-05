/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:32:53 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/24 19:23:29 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *ptr)
{
	t_philo	*philo;
	bool	setup;

	philo = (t_philo *)ptr;
	setup = wait_for_start(philo);
	while (setup)
	{
		if (!take_fork(philo->fork[0], *philo))
			break ;
		if (!take_fork(philo->fork[1], *philo))
		{
			set_value(&philo->fork[0]->take_fork, &philo->fork[0]->avail, true);
			break ;
		}
		if (!start_eating(philo) || ++philo->eat_count == philo->args->food_num
			|| !start_sleeping(*philo))
			break ;
	}
	if (!philo->args->finish && philo->eat_count != philo->args->food_num)
	{
		print_message(*philo, "died\n");
		set_value(&philo->args->finish_lock, &philo->args->finish, true);
	}
	free(philo);
	return (NULL);
}

bool	take_fork(t_fork *fork, t_philo philo)
{
	if (philo.args->finish)
		return (false);
	if (!fork->avail)
	{
		if (!print_message(philo, "is thinking\n"))
			return (false);
		while (!fork->avail)
		{
			if (!check_death(get_time_millisec(), philo))
				return (false);
		}
	}
	set_value(&fork->take_fork, &fork->avail, false);
	return (print_message(philo, "has taken a fork\n"));
}

bool	start_eating(t_philo *philo)
{
	int	start_time;

	if (philo->args->finish || !print_message(*philo, "is eating\n"))
	{
		release_forks(philo);
		return (false);
	}
	start_time = get_time_millisec();
	while (get_time_millisec() - start_time < philo->args->time_to_eat)
	{
		if (!check_death(get_time_millisec(), *philo))
		{
			release_forks(philo);
			return (false);
		}
		usleep(1 * 1000);
	}
	philo->last_meal = get_time_millisec();
	release_forks(philo);
	return (true);
}

bool	start_sleeping(t_philo philo)
{
	int	start_time;

	if (philo.args->finish || !print_message(philo, "is sleeping\n"))
		return (false);
	start_time = get_time_millisec();
	while (get_time_millisec() - start_time < philo.args->time_to_sleep)
	{
		if (!check_death(get_time_millisec(), philo))
			return (false);
		usleep(1 * 1000);
	}
	return (true);
}

bool	check_death(int cur_time, t_philo philo)
{
	int	time_passed;

	time_passed = cur_time - philo.last_meal;
	if (time_passed >= philo.args->time_to_die)
		return (false);
	return (true);
}
