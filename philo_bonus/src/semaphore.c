/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:33:41 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/30 20:07:28 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_sem_and_check_death(sem_t *sem, int index, t_philo *philo)
{
	sem_wait(sem);
	if (!check_death(philo))
	{
		if (sem_post(sem) == FAILURE)
			perror("sem_post");
		return (false);
	}
	philo->sems[index] = true;
	return (true);
}

void	post_all_sems(t_philo *philo)
{
	post_sem(philo->args->take_forks, &philo->sems[TAKE_FORKS]);
	post_sem(philo->args->forks_num, &philo->sems[FORK_1]);
	post_sem(philo->args->forks_num, &philo->sems[FORK_2]);
	post_sem(philo->args->forks_num, &philo->sems[PRINT]);
}

void	post_sem(sem_t *sem, bool *taken)
{
	if (*taken)
	{
		if (sem_post(sem) == FAILURE)
			perror("sem_post");
		*taken = false;
	}
}
