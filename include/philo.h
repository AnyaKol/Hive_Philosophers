/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:25:10 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/01 17:32:17 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "macros.h"
# include "structs.h"

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

extern volatile sig_atomic_t	g_last_sig;

int	print_error(t_error err, char *token);

/* ===== Memory arena ======================================================= */

#endif
