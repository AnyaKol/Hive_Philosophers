/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:25:23 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/29 16:01:25 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

typedef enum e_philo_sem
{
	TAKE_FORKS = 0,
	FORK_1,
	FORK_2,
	PRINT
}	t_philo_sem;

typedef struct s_args
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				food_num;
	int				start_time;
	bool			finish;
	sem_t			*take_forks;
	bool			can_take;
	sem_t			*forks_num;
	sem_t			*print;
}	t_args;

typedef struct s_data
{
	int		philos_num;
	pid_t	*pids;
	t_args	args;
}	t_data;

typedef struct s_philo
{
	int			index;
	int			last_meal;
	bool		sems[4];
	t_args		*args;
}	t_philo;

#endif
