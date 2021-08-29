/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 19:49:32 by rmander           #+#    #+#             */
/*   Updated: 2021/08/29 20:22:43 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "stack.h"
#include "utils.h"
#include "push_swap.h"

/*
* @brief Initial partition of stack A.
*
* Takes data in a stack A, puts it into B and groups data in chunks.
* Chunk items could not be sorted, but chunks grouped in a sorted order:
* chunk above contains integers, which are always bigger then integers in a chunk
* below.
*
* @param data Global state structure.
* @param divider Partition constant, which used to variate sizes of chunks.
*
* @return Nothing.
*/
void	chunking_initial(t_data *data, const double divider)
{
	t_chunk	*chunk;
	int		div;

	chunk = NULL;
	while (!empty(data->a) && !issorted(data->a->data, data->a->size, DESC))
	{
		chunk = lstadd_chunk(data);
		div = nth_element_copy(data, data->a->data, data->a->size, data->a->size / divider);
		while (find_lt(data->a->data, data->a->size, div) != -1)
		{
			if (*data->a->top < div)
			{
				op(data, "pb");
				chunk->size++;
			}
			else if (*data->a->data < div)
				op(data, "rra");
			else
				op(data, "ra");
		}
		chunk->top = data->b->top;
		if (data->a->size <= 5)
			push_swap45(data);
	}
}

static int	chunking_a_lt34(t_data *data, t_chunk *a_chunk)
{
	if (a_chunk->size == 3)
		if (ft_max(a_chunk->top - a_chunk->size + 1, a_chunk->size) == 0)
		{
			op(data, "sa");
			return (0) ;
		}
	if (a_chunk->size == 4)
	{
		op(data, "pb");
		op(data, "pb");
		if (a_chunk->top[0] > a_chunk->top[-1]
			&& data->b->top[0] < data->b->top[-1])
		{
			op(data, "ss");
			op(data, "pa");
			op(data, "pa");
			return (0);
		}
		op(data, "pa");
		op(data, "pa");
	}
	return (-1);
}

/*
* @brief Chunking of stack A part based on less than comparison.
*
* Having a chunk of data in stack A
* splits values by median and puts them into stack B. 
* Procedure repeats until chunk part gets sorted.
*
* @param data Global state structure.
* @param chunk Part of A stack put into chunk (with top and chunk size).
* 
* @return Nothing or exits in case of failure.
*/
void	chunking_a_lt(t_data *data, t_chunk *a_chunk)
{
	t_chunk	*b_chunk;

	b_chunk = NULL;
	while(!issorted(a_chunk->top - a_chunk->size + 1, a_chunk->size, DESC))
	{
		if (a_chunk->size == 2)
		{
			op(data, "sa");
			break ;
		}
		if (chunking_a_lt34(data, a_chunk) == 0)
			continue ;
		b_chunk = lstadd_chunk(data);
		b_chunk->size = partition_a_lt(data, a_chunk);
		b_chunk->top = data->b->top;
	}
}
