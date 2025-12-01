/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:32:53 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/30 20:53:22 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	take_forks(t_philo *philo);
static bool	start_eating(t_philo *philo);
static bool	start_sleeping(t_philo *philo);

void	routine(t_philo philo)
{
	int		eat_count;

	eat_count = 0;
	set_death_check(&philo);
	while (eat_count != philo.args->food_num)
	{
		if (!take_forks(&philo))
			break ;
		if (!start_eating(&philo) || ++eat_count == philo.args->food_num)
			break ;
		if (!start_sleeping(&philo))
			break ;
	}
	if (eat_count != philo.args->food_num)
	{
		print_message(&philo, "died\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

static bool	take_forks(t_philo *philo)
{
	if (!print_message(philo, "is thinking\n"))
		return (false);
	sem_wait(philo->args->forks_num);
	philo->sems[0] = true;
	if (!print_message(philo, "has taken a fork\n")
		|| !print_message(philo, "is thinking\n"))
	{
		post_philo_sem(philo->args->forks_num, &philo->sems[0]);
		return (false);
	}
	sem_wait(philo->args->forks_num);
	philo->sems[1] = true;
	if (!print_message(philo, "has taken a fork\n"))
	{
		post_philo_sem(philo->args->forks_num, &philo->sems[0]);
		post_philo_sem(philo->args->forks_num, &philo->sems[1]);
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
		result = print_message(philo, "is eating\n");
	if (result)
	{
		usleep(philo->args->time_to_eat * 1000);
		philo->last_meal = get_time_millisec();
	}
	post_philo_sem(philo->args->forks_num, &philo->sems[0]);
	post_philo_sem(philo->args->forks_num, &philo->sems[1]);
	return (result);
}

static bool	start_sleeping(t_philo *philo)
{
	if (!print_message(philo, "is sleeping\n"))
		return (false);
	usleep(philo->args->time_to_sleep * 1000);
	return (true);
}

bool	print_message(t_philo *philo, char *msg)
{
	int	time;
	int	cur_time;

	sem_wait(philo->args->print);
	philo->sems[2] = true;
	cur_time = get_time_millisec();
	if (cur_time == FAILURE)
	{
		post_philo_sem(philo->args->print, &philo->sems[2]);
		return (false);
	}
	time = cur_time - philo->args->start_time;
	if (printf("%d %d %s", time, philo->index, msg) == FAILURE)
	{
		perror("printf");
		post_philo_sem(philo->args->print, &philo->sems[2]);
		return (false);
	}
	post_philo_sem(philo->args->print, &philo->sems[2]);
	return (true);
}
