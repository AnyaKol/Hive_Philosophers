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
static void		unlink_sem(void);

bool	init_sem_parent(t_args *args, unsigned int philos_num)
{
	sem_unlink(SEM_FORKS_NUM);
	sem_unlink(SEM_PRINT);
	args->forks_num = open_sem(SEM_FORKS_NUM, philos_num);
	if (!args->forks_num)
	{
		unlink_sem();
		return (false);
	}
	args->print = open_sem(SEM_PRINT, 1);
	if (!args->print)
	{
		if (sem_close(args->forks_num) == FAILURE)
			perror("sem_close");
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

void	clean_up_parent(t_data data)
{
	if (sem_close(data.args.forks_num) == FAILURE)
		perror("sem_close");
	if (sem_close(data.args.print) == FAILURE)
		perror("sem_close");
	unlink_sem();
	free(data.pids);
}

static void	unlink_sem(void)
{
	if (sem_unlink(SEM_FORKS_NUM) == FAILURE)
		perror("sem_unlink");
	if (sem_unlink(SEM_PRINT) == FAILURE)
		perror("sem_unlink");
}

void	post_philo_sem(sem_t *sem, bool *taken)
{
	if (*taken)
	{
		if (sem_post(sem) == FAILURE)
			perror("sem_post");
		*taken = false;
	}
}
