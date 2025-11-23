/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:25:23 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/19 19:05:07 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_fork
{
	bool			avail;
	pthread_mutex_t	take_fork;
}	t_fork;

typedef struct s_args
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				food_num;
	int				start_time;
	pthread_mutex_t	print;
	bool			finish;
	pthread_mutex_t	finish_lock;
}	t_args;

typedef struct s_data
{
	int			philos_num;
	pthread_t	*philos;
	t_fork		*forks;
	t_args		args;
}	t_data;

typedef struct s_philo
{
	int		index;
	int		last_meal;
	t_args 	*args;
	t_fork	*fork[2];
}	t_philo;

#endif
