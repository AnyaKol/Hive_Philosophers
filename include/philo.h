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
bool	init_threads(t_data *data);


/* -----------  Libft func  ------------------------------------------------- */
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
int		ft_putendl_fd(char *s, int fd);
int		ft_strlen(const char *s);

#endif
