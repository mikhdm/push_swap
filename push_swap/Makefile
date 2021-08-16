# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/02 14:27:56 by rmander           #+#    #+#              #
#    Updated: 2021/08/16 18:28:45 by rmander          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = cc
INCLUDE = ./include
CFLAGS = -fsanitize=address -fsanitize=leak -g -Wall -Wextra -Werror -MMD -I $(INCLUDE) 
SRCS =  ./src/utils/alloca_to.c \
		./src/utils/ft_atoi.c \
		./src/utils/ft_atoss.c \
		./src/utils/ft_isdigit.c \
		./src/utils/ft_isspace.c \
		./src/utils/ft_memset.c \
		./src/utils/ft_memcpy.c \
		./src/utils/ft_strchr.c \
		./src/utils/ft_strdup_until.c \
		./src/utils/ft_strlen.c \
		./src/utils/ft_strlen_until.c \
		./src/utils/ft_qsort.c \
		./src/utils/issorted.c \
		./src/utils/swap.c \
		./src/utils/ft_lstadd_back.c \
		./src/utils/ft_lstdelone.c \
		./src/utils/ft_lstclear.c \
		./src/utils/ft_strcmp.c \
		./src/op.c \
		./src/push_swap.c \
		./src/error.c \
		./src/stackex.c \
		./src/stack.c \
		./src/main.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: $(NAME)

-include: $(DEPS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -rf $(OBJS)
	rm -rf $(DEPS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
