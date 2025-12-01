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

static sem_t	*open_sem(const char *name, unsigned int value);

bool	init_sems(t_args *args, unsigned int philos_num)
{
	sem_unlink(SEM_TAKE_FORKS);
	sem_unlink(SEM_FORKS_NUM);
	sem_unlink(SEM_PRINT);
	args->take_forks = open_sem(SEM_TAKE_FORKS, philos_num / 2);
	args->forks_num = open_sem(SEM_FORKS_NUM, philos_num);
	args->print = open_sem(SEM_PRINT, 1);
	if (!args->take_forks || !args->forks_num || !args->print)
	{
		sem_close(args->take_forks);
		sem_close(args->forks_num);
		sem_close(args->print);
		unlink_sem();
		return (false);
	}
	return (true);
}

static sem_t	*open_sem(const char *name, unsigned int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT, O_RDONLY, value);
	if (sem == SEM_FAILED)
	{
		perror("sem_open");
		return (NULL);
	}
	return (sem);
}

void	unlink_sem(void)
{
	if (sem_unlink(SEM_TAKE_FORKS) == FAILURE)
		perror("sem_unlink");
	if (sem_unlink(SEM_FORKS_NUM) == FAILURE)
		perror("sem_unlink");
	if (sem_unlink(SEM_PRINT) == FAILURE)
		perror("sem_unlink");
}

void	clean_up(t_data data)
{
	if (sem_close(data.args.take_forks) == FAILURE)
		perror("sem_close");
	if (sem_close(data.args.forks_num) == FAILURE)
		perror("sem_close");
	if (sem_close(data.args.print) == FAILURE)
		perror("sem_close");
	unlink_sem();
	free(data.pids);
}
