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

static bool	take_fork(t_fork *fork, t_philo philo);
static bool	start_eating(t_philo *philo);
static bool	start_sleeping(t_philo philo);
static bool	check_death(int cur_time, t_philo philo);

void	*routine(void *ptr)
{
	t_philo	*philo;
	int		eat_count;

	philo = (t_philo *)ptr;
	eat_count = 0;
	if (philo->args->food_num != 0)
	{
		while (1)
		{
			if (!take_fork(philo->fork[0], *philo)
				|| !take_fork(philo->fork[1], *philo))
				break ;
			if (!start_eating(philo))
				break ;
			if (++eat_count == philo->args->food_num)
				break ;
			if (!start_sleeping(*philo))
				break ;
		}
	}
	if (!philo->args->finish && eat_count != philo->args->food_num)
	{
		print_message(*philo, "died\n");
		set_value(&philo->args->finish_lock, &philo->args->finish, true);
	}
	free(philo);
	return (NULL);
}

static bool	take_fork(t_fork *fork, t_philo philo)
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
	return (print_message(philo,"has taken a fork\n"));
}

static bool	start_eating(t_philo *philo)
{
	if (philo->args->finish)
		return (false);
	if (!check_death(get_time_millisec() + philo->args->time_to_eat, *philo))
		return (false);
	if (!print_message(*philo, "is eating\n"))
		return (false);
	usleep(philo->args->time_to_eat * 1000);
	philo->last_meal = get_time_millisec();
	set_value(&philo->fork[0]->take_fork, &philo->fork[0]->avail, true);
	set_value(&philo->fork[1]->take_fork, &philo->fork[1]->avail, true);
	return (true);
}

static bool	start_sleeping(t_philo philo)
{
	if (philo.args->finish)
		return (false);
	if (!print_message(philo, "is sleeping\n"))
		return (false);
	while (get_time_millisec() - philo.last_meal < philo.args->time_to_sleep)
	{
		if (!check_death(get_time_millisec(), philo))
			return (false);
	}
	return (true);
}

static bool	check_death(int cur_time, t_philo philo)
{
	int	time_passed;

	time_passed = cur_time - philo.last_meal;
	if (time_passed >= philo.args->time_to_die)
		return (false);
	return (true);
}
