/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:25:40 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/29 16:20:55 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	if (!check_args(argc, argv, &data))
		return (EXIT_FAILURE);
	if (!init_sem(&data.args, (unsigned int) data.philos_num))
		return (EXIT_FAILURE);
	if (!fork_philos(data))
	{
		if (kill(0, SIGTERM) == FAILURE)
			perror("kill");
		unlink_sem();
		return (EXIT_FAILURE);
	}
	wait_for_philos(data);
	unlink_sem();
	return (EXIT_SUCCESS);
}

bool	fork_philos(t_data data)
{
	int		i;
	pid_t	pid;
	t_philo philo;

	i = 0;
	philo.args = &data.args;
	while (i < data.philos_num)
	{
		philo.index = i + 1;
		philo.last_meal = get_time_millisec();
		printf("Fork %d\n", i);//
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (false);
		}
		else if (pid == 0)
			routine(philo);
		i++;
	}
	return (true);
}

void	wait_for_philos(t_data data)
{
	int	status;
	int	i;

	i = 0;
	while (i < data.philos_num)
	{
		printf("Wait %d\n", i);//
		waitpid(-1, &status, 0);
		if (status == EXIT_FAILURE)
		{
			if (kill(0, SIGTERM) == FAILURE)
				perror("kill");
			return ;
		}
		i++;
	}
}
