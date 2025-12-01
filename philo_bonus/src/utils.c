/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:38:39 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/29 18:13:00 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_time_millisec(void)
{
	struct timeval	time;
	int				millisec;

	if (gettimeofday(&time, NULL) == FAILURE)
	{
		perror("gettimeofday");
		return (FAILURE);
	}
	millisec = (int) time.tv_sec * 1000 + (int) time.tv_usec / 1000;
	return (millisec);
}

bool	print_message(t_philo *philo, char *msg)
{
	int	time;
	int	cur_time;

	sem_wait(philo->args->print);
	philo->sems[PRINT] = true;
	cur_time = get_time_millisec();
	if (cur_time == FAILURE)
	{
		philo_post_all_sems(philo);
		return (false);
	}
	time = cur_time - philo->args->start_time;
	if (printf("%d %d %s", time, philo->index, msg) == FAILURE)
	{
		perror("printf");
		philo_post_all_sems(philo);
		return (false);
	}
	philo_post_sem(philo->args->print, &philo->sems[PRINT]);
	return (true);
}

void	philo_post_all_sems(t_philo *philo)
{
	philo_post_sem(philo->args->take_forks, &philo->sems[TAKE_FORKS]);
	philo_post_sem(philo->args->forks_num, &philo->sems[FORK_1]);
	philo_post_sem(philo->args->forks_num, &philo->sems[FORK_2]);
	philo_post_sem(philo->args->forks_num, &philo->sems[PRINT]);
}

void	philo_post_sem(sem_t *sem, bool *taken)
{
	if (*taken)
	{
		if (sem_post(sem) == FAILURE)
			perror("sem_post");
		*taken = false;
	}
}
