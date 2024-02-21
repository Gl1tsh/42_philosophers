# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nagiorgi <nagiorgi@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/15 13:54:45 by nagiorgi          #+#    #+#              #
#    Updated: 2024/02/21 15:03:38 by nagiorgi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BUILDDIR = build
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,$(BUILDDIR)/%.o,$(SRCS))
INCLUDES = ./include
NAME = philo
RM = rm -f
CFLAGS = -Wall #-Werror -Wextra
GCC = gcc

$(BUILDDIR)/%.o: src/%.c
			@mkdir -p $(BUILDDIR)
			@$(GCC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

$(NAME):	$(OBJS)
			@$(GCC) $(CFLAGS) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			@${RM} ${OBJS}

fclean:		clean
			@${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re
