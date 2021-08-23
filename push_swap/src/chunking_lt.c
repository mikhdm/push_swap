/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunking_lt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 04:37:08 by rmander           #+#    #+#             */
/*   Updated: 2021/08/23 04:47:34 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "utils.h"
#include "op.h"
#include "push_swap.h"

static	void	partition_lt_rra(t_data *data, t_chunk *chunk, size_t rac)
{
	while (rac--)
	{
		op(data, "rra");
		++chunk->top;
		++chunk->size;
	}
}

static size_t	partition_lt(t_data *data, t_chunk *chunk, int mid)
{
	size_t 	pbc;
	size_t	rac;

	pbc = 0;
	rac = 0;
	while (find_lt(chunk->top - chunk->size + 1, chunk->size, mid) != -1)
	{
		if (*chunk->top < mid)
		{
			op(data, "pb");
			++pbc;
		}
		else
		{
			op(data, "ra");
			++rac;
		}
		--chunk->top;
		--chunk->size;
	}
	partition_lt_rra(data, chunk, rac);
	return (pbc);
}

void	chunking_lt(t_data *data, t_chunk *chunk)
{
	size_t	sz;
	int		*bottom;

	sz = 0;
	bottom = chunk->top - chunk->size + 1;
	while((chunk->top != chunk->top - chunk->size)
			&& !issorted(bottom, chunk->size, FALSE))
		partition_lt(data, chunk,
			nth_element_copy(data, bottom, chunk->size, chunk->size / 2));
}
