/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:32:53 by akolupae          #+#    #+#             */
/*   Updated: 2025/12/20 15:32:54 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	take_forks(t_philo *philo);
static bool	start_eating(t_philo *philo);
static bool	start_sleeping(t_philo *philo);
static bool	print_message(t_philo *philo, char *msg);

void	routine(t_philo philo)
{
	int		eat_count;

	eat_count = 0;
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
		post_all_sems(&philo);
		exit(EXIT_FAILURE);
	}
	post_all_sems(&philo);
	exit(EXIT_SUCCESS);
}

static bool	take_forks(t_philo *philo)
{
	if (!print_message(philo, "is thinking\n"))
		return (false);
	if (!wait_sem_and_check_death(philo->args->queue, QUEUE, philo))
		return (false);
	if (!wait_sem_and_check_death(philo->args->take_forks, TAKE_FORKS, philo))
		return (false);
	if (!wait_sem_and_check_death(philo->args->forks_num, FORK_1, philo))
		return (false);
	if (!print_message(philo, "has taken a fork\n")
		|| !print_message(philo, "is thinking\n"))
		return (false);
	if (!philo->args->can_take)
	{
		while (check_death(*philo))
			usleep(1 * 1000);
		return (false);
	}
	if (!wait_sem_and_check_death(philo->args->forks_num, FORK_2, philo))
		return (false);
	if (!print_message(philo, "has taken a fork\n"))
		return (false);
	post_sem(philo->args->queue, &philo->sems[QUEUE]);
	return (true);
}

static bool	start_eating(t_philo *philo)
{
	int	start_time;

	if (!print_message(philo, "is eating\n"))
		return (false);
	start_time = get_time_millisec();
	while (get_time_millisec() - start_time < philo->args->time_to_eat)
	{
		if (!check_death(*philo))
			return (false);
		usleep(1 * 1000);
	}
	philo->last_meal = get_time_millisec();
	post_sem(philo->args->forks_num, &philo->sems[FORK_1]);
	post_sem(philo->args->forks_num, &philo->sems[FORK_2]);
	post_sem(philo->args->take_forks, &philo->sems[TAKE_FORKS]);
	return (true);
}

static bool	start_sleeping(t_philo *philo)
{
	int	start_time;

	if (!print_message(philo, "is sleeping\n"))
		return (false);
	start_time = get_time_millisec();
	while (get_time_millisec() - start_time < philo->args->time_to_sleep)
	{
		if (!check_death(*philo))
			return (false);
		usleep(1 * 1000);
	}
	return (true);
}

static bool	print_message(t_philo *philo, char *msg)
{
	int	time;
	int	cur_time;

	sem_wait(philo->args->print);
	philo->sems[PRINT] = true;
	cur_time = get_time_millisec();
	if (cur_time == FAILURE)
		return (false);
	time = cur_time - philo->args->start_time;
	if (printf("%d %d %s", time, philo->index, msg) == FAILURE)
		return (false);
	post_sem(philo->args->print, &philo->sems[PRINT]);
	return (true);
}
