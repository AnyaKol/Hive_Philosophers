/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:25:10 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/19 19:00:45 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# include "macros.h"
# include "structs.h"

bool	check_args(int argc, char **argv, t_data *data);
bool	init_data(t_data *data);
void	free_data(t_data *data);
bool	init_and_join_threads(t_data *data);
bool	wait_for_start(t_philo *philo);
void	*routine(void *ptr);
bool	take_fork(t_fork *fork, t_philo *philo);
bool	start_eating(t_philo *philo);
bool	start_sleeping(t_philo *philo);
bool	check_death(int cur_time, t_philo philo);
bool	check_eat_count(t_philo *philo);
void	release_forks(t_philo *philo);
void	set_value(pthread_mutex_t *mutex, bool *var, bool value);
bool	print_message(t_philo *philo, char *msg, int status);
int		get_time_millisec(void);

/* -----------  Libft func  ------------------------------------------------- */
int		ft_atoi(const char *nptr);
bool	ft_isdigit(int c);
int		ft_putendl_fd(char *s, int fd);
int		ft_strlen(const char *s);

#endif
