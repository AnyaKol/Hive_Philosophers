/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 18:33:41 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/24 19:28:01 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init(t_args *args, unsigned int philos_num)
{
	args->fork_num = sem_open(SEM_NAME, O_CREAT | O_EXCL, O_RDONLY,
		philos_num);
	if (args->fork_num == SEM_FAILED)
	{
		perror("sem_open");
		return (false);
	}
	return (true);
}
