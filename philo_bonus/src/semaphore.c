/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:33:41 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/29 18:06:20 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	open_and_close(sem_t *sem, const char *name, unsigned int value);

bool	init_sem(t_args *args, unsigned int philos_num)
{
	if (!open_and_close(args->forks_num, SEM_FORKS_NUM, philos_num - 1))
	{
		unlink_sem();
		return (false);
	}
	if (!open_and_close(args->print, SEM_PRINT, 0))
	{
		unlink_sem();
		return (false);
	}
	return (true);
}

static bool	open_and_close(sem_t *sem, const char *name, unsigned int value)
{
	sem = sem_open(name, O_CREAT, O_RDONLY, value);
	if (sem == SEM_FAILED)
	{
		perror("sem_open");
		return (false);
	}
	if (sem_close(sem) == FAILURE)
	{
		perror("sem_close");
		return (false);
	}
	return (true);
}

void	unlink_sem(void)
{
	if (sem_unlink(SEM_FORKS_NUM) == FAILURE)
		perror("sem_unlink");
	if (sem_unlink(SEM_PRINT) == FAILURE)
		perror("sem_unlink");
}
