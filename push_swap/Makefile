# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/02 14:27:56 by rmander           #+#    #+#              #
#    Updated: 2021/08/03 02:38:19 by mikhaylen        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = cc
INCLUDE = ./include
CFLAGS = -g -fsanitize=address -fsanitize=leak -Wall -Wextra -Werror -MMD -I$(INCLUDE) 
SRCS =  ./src/utils/alloca_to.c \
		./src/utils/ft_atoi.c \
		./src/utils/ft_isdigit.c \
		./src/utils/ft_isspace.c \
		./src/utils/ft_memset.c \
		./src/utils/ft_strchr.c \
		./src/utils/ft_strdup_until.c \
		./src/utils/ft_strlen.c \
		./src/utils/ft_strlen_until.c \
		./src/error.c \
		./src/stack.c \
		./src/main.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: $(NAME)

-include: $(DEPS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -rf $(OBJS)
	rm -rf $(DEPS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
