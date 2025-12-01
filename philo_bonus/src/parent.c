/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:25:40 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/29 16:20:55 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	fork_philos(t_data data)
{
	int		i;
	t_philo	philo;

	i = 0;
	philo.args = &data.args;
	philo.sems[TAKE_FORKS] = false;
	philo.sems[FORK_1] = false;
	philo.sems[FORK_2] = false;
	philo.sems[PRINT] = false;
	while (i < data.philos_num)
	{
		philo.index = i + 1;
		philo.last_meal = get_time_millisec();
		data.pids[i] = fork();
		if (data.pids[i] < 0)
		{
			perror("fork");
			return (false);
		}
		else if (data.pids[i] == 0)
			routine(philo);
		i++;
	}
	return (true);
}

void	wait_for_philos(t_data data)
{
	int		status;
	pid_t	term;
	int		i;

	i = 0;
	while (i < data.philos_num)
	{
		term = waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == EXIT_FAILURE)
		{
			kill_philos(data, term);
			return ;
		}
		i++;
	}
}

void	kill_philos(t_data data, pid_t term)
{
	int	i;

	i = 0;
	while (i < data.philos_num)
	{
		if (term == 0 || data.pids[i] != term)
		{
			if (kill(data.pids[i], SIGTERM) == FAILURE)
				perror("kill");
		}
		i++;
	}
}
