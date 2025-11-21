/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:32:53 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/21 14:11:34 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (fork[0]->avail)
		take_fork(fork[0], philo->args->print);
	if (fork[1]->avail)
		take_fork(fork[0], &philo->args->print, philo->index);
	start_eating(philo->args->print);
}

void	take_fork(t_fork *fork, pthread_mutex_t *print, int index)
{
	//lock fork
	fork->avail = false;
	//unlock fork
	print_message(index,"took fork\n", print);
}

void	print_message(int index, char *msg, pthread_mutex_t *print)
{
	//lock print
	printf("%d %s", index, msg);
	//unlock print
}
