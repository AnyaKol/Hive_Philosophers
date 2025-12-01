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

static void	set_philo_init_state(t_philo *philo, t_args *args);

bool	fork_philos(t_data data)
{
	int		i;
	t_philo	philo;

	i = 0;
	set_philo_init_state(&philo, &data.args);
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
		{
			free(data.pids);
			routine(philo);
		}
		i++;
	}
	return (true);
}

static void	set_philo_init_state(t_philo *philo, t_args *args)
{
	philo->args = args;
	philo->sems[TAKE_FORKS] = false;
	philo->sems[FORK_1] = false;
	philo->sems[FORK_2] = false;
	philo->sems[PRINT] = false;
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
