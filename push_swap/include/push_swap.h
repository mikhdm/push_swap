/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:08:55 by rmander           #+#    #+#             */
/*   Updated: 2021/08/24 00:40:58 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "stack.h"

# define ASC	1
# define DESC	0

typedef struct s_chunk
{
	size_t	size;
	int		*top;
}	t_chunk;

void	push_swap(t_data *data);
size_t	partition_b_gt(t_data *data, t_chunk *chunk, int mid);
size_t	partition_a_lt(t_data *data, t_chunk *chunk, int mid);
void	chunking_a_lt(t_data *data, t_chunk *chunk);
t_chunk	*lstadd_chunk(t_data *data);

/* TODO REMOVE! */

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define NC "\033[0m"

void	debug(t_stack *stack, char *color);

#endif
