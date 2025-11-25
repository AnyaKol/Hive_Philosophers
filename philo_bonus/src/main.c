/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:25:40 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/25 10:47:30 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	if (!check_args(argc, argv, &data))
		return (EXIT_FAILURE);
	if (!init(&data.args, (unsigned int) data.philos_num))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
