/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:25:23 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/25 10:46:55 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

typedef struct s_args
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				food_num;
	int				start_time;
	bool			finish;
	sem_t			*fork_num;
	sem_t			print;
}	t_args;

typedef struct s_data
{
	int			philos_num;
	t_args		args;
}	t_data;

typedef struct s_philo
{
	int		index;
	int		last_meal;
	t_args	*args;
}	t_philo;

#endif
