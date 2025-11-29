/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:32:53 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/29 18:10:05 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	take_forks(t_philo philo);
static bool	start_eating(t_philo *philo);
static bool	start_sleeping(t_philo philo);
static bool	check_death(int cur_time, t_philo philo);

void	routine(t_philo philo)
{
	int		eat_count;

	eat_count = 0;
	while (eat_count != philo.args->food_num)
	{
		if (!take_forks(philo))
			break ;
		if (!start_eating(&philo) || ++eat_count == philo.args->food_num)
			break ;
		if (!start_sleeping(philo))
			break ;
	}
	if (eat_count != philo.args->food_num)
	{
		print_message(philo, "died\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

static bool	take_forks(t_philo philo)
{
	sem_wait(philo.args->forks_num);
	if (!check_death(get_time_millisec(), philo)
		|| !print_message(philo, "has taken a fork\n"))
	{
		if (sem_post(philo.args->forks_num) == FAILURE)
			perror("sem_post");
		return (false);
	}
	sem_wait(philo.args->forks_num);
	if (!print_message(philo, "has taken a fork\n"))
	{
		if (sem_post(philo.args->forks_num) == FAILURE)
			perror("sem_post");
		if (sem_post(philo.args->forks_num) == FAILURE)
			perror("sem_post");
		return (false);
	}
	return (true);
}

static bool	start_eating(t_philo *philo)
{
	bool	result;

	result = check_death(get_time_millisec() + philo->args->time_to_eat,
		*philo);
	if (result)
		result = print_message(*philo, "is eating\n");
	if (result)
	{
		usleep(philo->args->time_to_eat * 1000);
		philo->last_meal = get_time_millisec();
	}
	if (sem_post(philo->args->forks_num) == FAILURE)
		perror("sem_post");
	if (sem_post(philo->args->forks_num) == FAILURE)
		perror("sem_post");
	return (result);
}

static bool	start_sleeping(t_philo philo)
{
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
