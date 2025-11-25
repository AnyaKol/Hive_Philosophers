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
# include <signal.h>
# include <semaphore.h>

# include "macros_bonus.h"
# include "structs_bonus.h"

bool	check_args(int argc, char **argv, t_data *data);
int		get_time_millisec(void);

/* -----------  Libft func  ------------------------------------------------- */
int		ft_atoi(const char *nptr);
bool	ft_isdigit(int c);
int		ft_putendl_fd(char *s, int fd);
int		ft_strlen(const char *s);

#endif
