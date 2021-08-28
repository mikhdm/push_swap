/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 19:46:03 by rmander           #+#    #+#             */
/*   Updated: 2021/08/28 22:07:20 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"
#include "stack.h"
#include "op.h"
#include <stdio.h>

static	void	partition_a_lt_rra(t_data *data, t_chunk *chunk, size_t ra_cnt)
{
	while (ra_cnt--)
	{
		op(data, "rra");
		++chunk->size;
	}
}

static	void	partition_b_gt_rrb(t_data *data, t_chunk *chunk, size_t rb_cnt)
{
	while (rb_cnt--)
	{
		op(data, "rrb"); 
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
* 
* @return Count of elements put into stack B.
*/
size_t	partition_a_lt(t_data *data, t_chunk *chunk)
{
	size_t 	pb_cnt;
	size_t	ra_cnt;
	int		mid;

	pb_cnt = 0;
	ra_cnt = 0;
	mid = nth_element_copy(data, chunk->top - chunk->size + 1,
			chunk->size, chunk->size / 2);
	while (find_lt(chunk->top - chunk->size + 1, chunk->size, mid) != -1)
	{
		if (*chunk->top < mid)
		{
			op(data, "pb");
			++pb_cnt;
			--chunk->top;
		}
		else
		{
			op(data, "ra");
			++ra_cnt;
		}
		--chunk->size;
	}
	partition_a_lt_rra(data, chunk, ra_cnt);
	return (pb_cnt);
}

/*
* @brief Partitioning of stack B part. 
*
* Having a chunk of data in stack B
* splits values by median and puts them into stack A. 
*
* @param data Global state structure.
* @param chunk Part of B stack put into chunk (with top and chunk size).
* 
* @return Count of elements put into stack A.
*/
size_t	partition_b_gt(t_data *data, t_chunk *chunk, int is_lastchunk)
{
	size_t	pa_cnt;
	size_t	rb_cnt;
	int		mid;

	pa_cnt = 0;
	rb_cnt = 0;
	mid = nth_element_copy(data, chunk->top - chunk->size + 1,
			chunk->size, chunk->size / 2);
	if (!is_lastchunk)
	{
		while (find_gt(chunk->top - chunk->size + 1, chunk->size, mid) != -1)
		{
			if (*chunk->top > mid)
			{
				op(data, "pa");
				++pa_cnt;
				--chunk->top;
			}
			else
			{
				op(data, "rb");
				++rb_cnt;
			}
			--chunk->size;
		}
		partition_b_gt_rrb(data, chunk, rb_cnt);
	}
	else
	{
		while(find_gt(chunk->top - chunk->size + 1, chunk->size, mid) != -1)
		{
			if (*chunk->top > mid)
			{
				op(data, "pa");
				++pa_cnt;
				--chunk->top;
				--chunk->size;
			}
			else if (*(chunk->top - chunk->size + 1) > mid)
				op(data, "rrb");
			else
				op(data, "rb");
		}
	}
	return (pa_cnt);
}
