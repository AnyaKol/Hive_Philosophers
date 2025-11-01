# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/01 17:23:31 by akolupae          #+#    #+#              #
#    Updated: 2025/11/01 17:24:15 by akolupae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------  VARS  -------------------------------------------------------- #
NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinclude -MMD -MP

INCDIR = include

SRC = \
	main.c \
	check_args.c \

OBJDIR = obj
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEF = $(OBJ:.o=.d)

# ------------  HEADER  ------------------------------------------------------ #
HEADER = \
	$(INCDIR)/philo.h \
	$(INCDIR)/structs.h \
	$(INCDIR)/macros.h \

# ------------  RULES  ------------------------------------------------------- #
all: $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# ------------  EXTRA  ------------------------------------------------------- #
.SECONDARY: $(OBJDIR) $(OBJ)
.PHONY: all clean fclean re
#.SILENT:

-include $(DEF)
