/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_g.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 01:07:07 by rmander           #+#    #+#             */
/*   Updated: 2021/08/30 01:20:26 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"
#include "stack.h"
#include "op.h"
#include <stddef.h>

static int	push_swap_g_sorted(t_data *data, t_chunk *b_chunk, t_list **node)
{
	if (!b_chunk->top)
	{
		*node = (*node)->next;
		return (0);
	}
	if (issorted(b_chunk->top - b_chunk->size + 1, b_chunk->size, ASC))
	{
		while (b_chunk->size--)
			op(data, "pa");
		b_chunk->top = NULL;
		b_chunk->size = 0;
		*node = (*node)->next;
		return (0);
	}
	if (b_chunk->size == 2)
	{
		if (*b_chunk->top < *(b_chunk->top - 1))
			op(data, "sb");
		return (0);
	}
	return (-1);
}

/*
* @brief Main routing for data sorting.
*
* Quick sort analog involved here. At first data goes into stack B
* as groups of integers (chunking_initial), where every chunk above
* contains integers bigger than in a chunk below.
*
* @param data Global state structure.
* @param div Partition divider for chunking_initial routine.
*
* @return Nothing.
*/
void	push_swap_g(t_data *data, const double div)
{
	t_chunk	a_chunk;
	t_chunk	*b_chunk;
	t_list	*node;
	size_t	sz;
	int		is_lastchunk;

	if (issorted(data->a->data, data->a->size, DESC))
		return ;
	chunking_initial(data, div);
	a_chunk = (t_chunk){.top = NULL, .size = 0};
	b_chunk = NULL;
	node = data->chunks;
	while (node)
	{
		is_lastchunk = !node->next;
		b_chunk = (t_chunk *)node->content;
		if (push_swap_g_sorted(data, b_chunk, &node) == 0)
			continue ;
		sz = partition_b_gt(data, b_chunk, is_lastchunk);
		a_chunk.size = sz;
		a_chunk.top = data->a->top;
		chunking_a_lt(data, &a_chunk);
		node = data->chunks;
	}
}
