/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:32:53 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/30 20:53:22 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*exit_on_death(void *ptr);

void	set_death_check(t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, exit_on_death, (void *) philo)
		!= SUCCESS)
	{
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	if (pthread_detach(philo->thread) != SUCCESS)
	{
		perror("pthread_detach");
		exit(EXIT_FAILURE);
	}
}

static void	*exit_on_death(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (true)
	{
		if (!check_death(get_time_millisec(), *philo))
		{
			post_philo_sem(philo->args->forks_num, &philo->sems[0]);
			post_philo_sem(philo->args->forks_num, &philo->sems[1]);
			print_message(philo, "died\n");
			exit(EXIT_FAILURE);
		}
	}
}

bool	check_death(int cur_time, t_philo philo)
{
	int	time_passed;

	time_passed = cur_time - philo.last_meal;
	if (time_passed >= philo.args->time_to_die)
		return (false);
	return (true);
}
