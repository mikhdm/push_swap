/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 19:46:03 by rmander           #+#    #+#             */
/*   Updated: 2021/08/24 00:40:54 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"
#include "stack.h"
#include "op.h"

static	void	partition_a_lt_rra(t_data *data, t_chunk *chunk, size_t rac)
{
	while (rac--)
	{
		op(data, "rra");
		++chunk->top;
		++chunk->size;
	}
}

static	void	partition_b_gt_rrb(t_data *data, t_chunk *chunk, size_t rbc)
{
	while (rbc--)
	{
		op(data, "rrb"); 
		++chunk->top;
		++chunk->size;
	}
}

/*
* @brief Partitioning of stack A part. 
*
* Having a chunk of data in stack A
* splits values by median and puts them into stack B. 
*
* @param data Global state structure.
* @param chunk Part of A stack put into chunk (with top and chunk size).
* @param mid Median value from chunk given.
* 
* @return Count of elements put into stack B.
*/
size_t	partition_a_lt(t_data *data, t_chunk *chunk, int mid)
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
	partition_a_lt_rra(data, chunk, rac);
	return (pbc);
}

/*
* @brief Partitioning of stack B part. 
*
* Having a chunk of data in stack B
* splits values by median and puts them into stack A. 
*
* @param data Global state structure.
* @param chunk Part of B stack put into chunk (with top and chunk size).
* @param mid Median value from chunk given.
* 
* @return Count of elements put into stack A.
*/
size_t	partition_b_gt(t_data *data, t_chunk *chunk, int mid)
{
	size_t	pac;
	size_t	rbc;

	pac = 0;
	rbc = 0;
	while (find_gt(chunk->top - chunk->size + 1, chunk->size, mid) != -1)
	{
		if (*chunk->top > mid)
		{
			op(data, "pa");
			++pac;
		}
		else
		{
			op(data, "rb");
			++rbc;
		}
		/* TODO needs fix: size and top unchanged if rb */
		--chunk->top;
		--chunk->size;
	}
	partition_b_gt_rrb(data, chunk, rbc);
	return (pac);
}
