# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/02 14:27:56 by rmander           #+#    #+#              #
#    Updated: 2021/08/30 20:18:20 by rmander          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
BONUS = checker
CC = clang
INCLUDE = ./include
# CFLAGS = -fsanitize=address -fsanitize=leak -g -Wall -Wextra -Werror -MMD -I $(INCLUDE)
CFLAGS = -O3 -Wall -Wextra -Werror -MMD -I $(INCLUDE)
SRCS =  ./src/utils/alloca_to.c \
		./src/utils/ft_atoi.c \
		./src/utils/ft_atoss.c \
		./src/utils/ft_isdigit.c \
		./src/utils/ft_isspace.c \
		./src/utils/ft_memset.c \
		./src/utils/ft_memcpy.c \
		./src/utils/ft_strchr.c \
		./src/utils/ft_strdup_until.c \
		./src/utils/ft_strlen_until.c \
		./src/utils/ft_qsort.c \
		./src/utils/issorted.c \
		./src/utils/swap.c \
		./src/utils/nth_element.c \
		./src/utils/nth_element_copy.c \
		./src/utils/ft_min.c \
		./src/utils/ft_max.c \
		./src/utils/ft_lstnew.c \
		./src/utils/ft_lstiter.c \
		./src/utils/ft_lstadd_back.c \
		./src/utils/ft_lstadd_front.c \
		./src/utils/ft_lstdelone.c \
		./src/utils/ft_lstclear.c \
		./src/utils/ft_lstsize.c \
		./src/utils/ft_strcmp.c \
		./src/utils/find_gt.c \
		./src/utils/find_lt.c \
		./src/utils/ft_linsearch.c \
		./src/utils/iarrdup.c \
		./src/utils/put_op.c \
		./src/op.c \
		./src/parse.c \
		./src/optimize.c \
		./src/chunking.c \
		./src/partition_a.c \
		./src/partition_b.c \
		./src/push_swap.c \
		./src/push_swap_g.c \
		./src/error.c \
		./src/stackex.c \
		./src/stack.c \
		./src/main.c

CHECKERSRCS =	./src/utils/alloca_to.c \
				./src/utils/get_next_line_utils.c \
				./src/utils/ft_atoi.c \
				./src/utils/ft_isdigit.c \
				./src/utils/ft_isspace.c \
				./src/utils/ft_linsearch.c \
				./src/utils/ft_memset.c \
				./src/utils/ft_qsort.c \
				./src/utils/ft_atoss.c \
				./src/utils/get_next_line.c \
				./src/utils/ft_strlcpy.c \
				./src/utils/ft_strjoin.c \
				./src/utils/ft_memcpy.c \
				./src/utils/ft_strchr.c \
				./src/utils/ft_strdup_until.c \
				./src/utils/ft_strlen_until.c \
				./src/utils/ft_strcmp.c \
				./src/utils/ft_lstnew.c \
				./src/utils/ft_lstiter.c \
				./src/utils/ft_lstadd_back.c \
				./src/utils/ft_lstdelone.c \
				./src/utils/ft_lstclear.c \
				./src/utils/issorted.c \
				./src/utils/swap.c \
				./src/error.c \
				./src/stackex.c \
				./src/stack.c \
				./src/op.c \
				./src/parse.c \
				./src/optimize.c \
				./src/checker/reader.c \
				./src/checker/checker.c

OBJS = $(SRCS:.c=.o)
CHECKEROBJS = $(CHECKERSRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
CHECKERDEPS = $(CHECKERSRCS:.c=.d) 

all: $(NAME)

bonus: $(BONUS)

-include $(DEPS)
-include $(CHECKERDEPS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BONUS): $(CHECKEROBJS) $(NAME)
	$(CC) $(CFLAGS) $(CHECKEROBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -rf $(OBJS)
	rm -rf $(CHECKEROBJS)
	rm -rf $(DEPS)
	rm -rf $(CHECKERDEPS)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BONUS)

re: fclean all

.PHONY: all clean fclean re
