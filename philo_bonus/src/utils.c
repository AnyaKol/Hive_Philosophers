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

bool	check_death(t_philo philo)
{
	int	time_passed;

	time_passed = get_time_millisec() - philo.last_meal;
	if (time_passed >= philo.args->time_to_die)
		return (false);
	return (true);
}
