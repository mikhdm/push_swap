/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:08:55 by rmander           #+#    #+#             */
/*   Updated: 2021/08/29 10:45:54 by rmander          ###   ########.fr       */
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

void	push_swap45(t_data *data);
void	push_swap(t_data *data, const double div);
size_t	partition_b_gt(t_data *data, t_chunk *chunk, int is_lastchunk);
size_t	partition_a_lt(t_data *data, t_chunk *chunk);
void	chunking_initial(t_data *data, const double divider);
void	chunking_a_lt(t_data *data, t_chunk *chunk);
t_chunk	*lstadd_chunk(t_data *data);

#endif
