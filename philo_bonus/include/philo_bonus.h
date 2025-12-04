/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:25:10 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/25 11:23:46 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdbool.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <pthread.h>

# include "macros_bonus.h"
# include "structs_bonus.h"

bool	check_args(int argc, char **argv, t_data *data);
bool	init_pids(t_data *data);
bool	init_sems(t_args *args, unsigned int philos_num);
void	clean_up(t_data data);
void	unlink_sem(void);

/* -----------  Parent process  --------------------------------------------- */
bool	fork_philos(t_data data);
void	wait_for_philos(t_data data);
void	kill_philos(t_data data, pid_t term);

/* -----------  Child process  ---------------------------------------------- */
void	routine(t_philo philo);
void	wait_sem_and_check_death(sem_t *sem, int index, t_philo *philo);
void	post_all_sems(t_philo *philo);
void	post_sem(sem_t *sem, bool *taken);
int		get_time_millisec(void);
bool	check_death(int cur_time, t_philo philo);

/* -----------  Libft func  ------------------------------------------------- */
int		ft_atoi(const char *nptr);
bool	ft_isdigit(int c);
int		ft_putendl_fd(char *s, int fd);
int		ft_strlen(const char *s);

#endif
