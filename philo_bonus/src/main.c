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
	if (!check_args(argc, argv, &data) || !init_pids(&data))
		return (EXIT_FAILURE);
	if (!init_sems(&data.args, (unsigned int) data.philos_num))
	{
		free(data.pids);
		return (EXIT_FAILURE);
	}
	if (!fork_philos(data))
	{
		kill_philos(data, 0);
		clean_up(data);
		return (EXIT_FAILURE);
	}
	wait_for_philos(data);
	clean_up(data);
	return (EXIT_SUCCESS);
}
