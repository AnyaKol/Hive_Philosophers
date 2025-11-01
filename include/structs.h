/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:25:23 by akolupae          #+#    #+#             */
/*   Updated: 2025/11/01 17:25:30 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* ================ ENUM ==================================================== */
typedef enum e_type
{
	COMMAND,
	BUILTIN,
	ARG,
	FILENAME,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND
}	t_type;

/* ================ TOKEN =================================================== */
typedef struct s_tokens
{
	char		**values;
	t_type		*types;
	int			size;
}	t_tokens;

#endif
