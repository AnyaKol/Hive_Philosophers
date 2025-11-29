/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:38:39 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/29 18:13:00 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_time_millisec(void)
{
	struct timeval	time;
	int				millisec;

	if (gettimeofday(&time, NULL) == FAILURE)
	{
		perror("gettimeofday");
		return (FAILURE);
	}
	millisec = (int) time.tv_sec * 1000 + (int) time.tv_usec / 1000;
	return (millisec);
}

bool	print_message(t_philo philo, char *msg)
{
	int	time;
	int	cur_time;

	sem_wait(philo.args->print);
	cur_time = get_time_millisec();
	if (cur_time == FAILURE)
	{
		if (sem_post(philo.args->print) == FAILURE)
			perror("sem_post");
		return (false);
	}
	time = cur_time - philo.args->start_time;
	if (printf("%d %d %s", time, philo.index, msg) == FAILURE)
	{
		perror("printf");
		if (sem_post(philo.args->print) == FAILURE)
			perror("sem_post");
		return (false);
	}
	if (sem_post(philo.args->print) == FAILURE)
		perror("sem_post");
	return (true);
}
