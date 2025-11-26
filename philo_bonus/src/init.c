/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:33:41 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/26 20:14:34 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init(t_args *args, unsigned int philos_num)
{
	args->fork_num = sem_open(SEM_FORK_NUM, O_CREAT | O_EXCL, O_RDONLY,
		philos_num);
	args->print = sem_open(SEM_PRINT, O_CREAT | O_EXCL, O_RDONLY, 0);
	if (args->fork_num == SEM_FAILED || args->print == SEM_FAILED)
	{
		perror("sem_open");
		return (false);
	}
	return (true);
}

bool	fork_philos(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->philos_num)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (false);
		}
		else if (pid == 0)
			routine(data->args);
		i++;
	}
}
