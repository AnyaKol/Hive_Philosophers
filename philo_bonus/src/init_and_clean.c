/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:25:40 by akolupae          #+#    #+#             */
/*   Updated: 2025/12/22 09:33:23 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static sem_t	*open_sem(const char *name, unsigned int value);

bool	init_pids(t_data *data)
{
	data->pids = malloc(data->philos_num * sizeof(pid_t));
	if (!data->pids)
		return (false);
	return (true);
}

bool	init_sems(t_args *args, unsigned int philos_num)
{
	unlink_sem();
	args->take_forks = open_sem(SEM_TAKE_FORKS, 1);
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
		return (NULL);
	return (sem);
}

void	clean_up(t_data data)
{
	if (data.pids)
		free(data.pids);
	sem_close(data.args.take_forks);
	sem_close(data.args.forks_num);
	sem_close(data.args.print);
	unlink_sem();
}

void	unlink_sem(void)
{
	sem_unlink(SEM_TAKE_FORKS);
	sem_unlink(SEM_FORKS_NUM);
	sem_unlink(SEM_PRINT);
}
