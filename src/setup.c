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

static bool	setup_even(t_philo *philo);
static bool	setup_odd_one(t_philo *philo);

bool	wait_for_start(t_philo *philo)
{
	while (!philo->args->start)
		continue ;
	philo->last_meal = philo->args->start_time;
	if (philo->index % 2 == 0)
		return (setup_even(philo));
	else if (philo->args->odd && philo->index == 1)
		return (setup_odd_one(philo));
	else if (philo->index % 2 == 1)
	{
		while (philo->fork[0]->avail && !philo->args->finish
			&& check_death(get_time_millisec(), *philo))
			continue ;
	}
	return (true);
}

static bool	setup_even(t_philo *philo)
{
	if (!take_fork(philo->fork[0], *philo))
		return (false);
	if (!take_fork(philo->fork[1], *philo))
	{
		set_value(&philo->fork[0]->take_fork, &philo->fork[0]->avail, true);
		return (false);
	}
	if (!start_eating(philo) || ++philo->eat_count == philo->args->food_num
		|| !start_sleeping(*philo))
		return (false);
	return (true);
}

static bool	setup_odd_one(t_philo *philo)
{
	if (!take_fork(philo->fork[0], *philo))
		return (false);
	while (philo->fork[1]->avail && !philo->args->finish
		&& check_death(get_time_millisec(), *philo))
		continue ;
	if (!take_fork(philo->fork[1], *philo))
	{
		set_value(&philo->fork[0]->take_fork, &philo->fork[0]->avail, true);
		return (false);
	}
	if (!start_eating(philo) || ++philo->eat_count == philo->args->food_num
		|| !start_sleeping(*philo))
		return (false);
	return (true);
}
