# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/01 17:23:31 by akolupae          #+#    #+#              #
#    Updated: 2025/11/25 10:48:26 by akolupae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------  VARS  -------------------------------------------------------- #
NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(INCDIR) -MMD -MP
INCDIR = include

SRCDIR = src
SRC = \
	main.c \
	check_args.c \

OBJDIR = obj
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

DEF = $(OBJ:.o=.d)

# ------------  HEADER  ------------------------------------------------------ #
HEADER = \
	$(INCDIR)/philo_bonus.h \
	$(INCDIR)/structs_bonus.h \
	$(INCDIR)/macros_bonus.h \

# ------------  RULES  ------------------------------------------------------- #
all: $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/libft_fun/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJDIR) $(OBJ) $(HEADER)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# ------------  EXTRA  ------------------------------------------------------- #
.SECONDARY: $(OBJDIR) $(OBJ)
.PHONY: all clean fclean re

-include $(DEF)
