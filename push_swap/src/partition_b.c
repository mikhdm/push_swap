/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 19:46:03 by rmander           #+#    #+#             */
/*   Updated: 2021/08/29 23:48:46 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"
#include "stack.h"
#include "op.h"

static	void	partition_b_gt_rrb(t_data *data, t_chunk *chunk, size_t rb_cnt)
{
	while (rb_cnt--)
	{
		op(data, "rrb"); 
		++chunk->size;
	}
}

static size_t	partition_b_gt_basic(t_data *data, t_chunk *chunk, int div)
{
	size_t	pa_cnt;
	size_t	rb_cnt;	

	pa_cnt = 0;
	rb_cnt = 0;
	while (find_gt(chunk->top - chunk->size + 1, chunk->size, div) != -1)
	{
		if (*chunk->top > div)
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
	if (chunk->size >= 2 && *chunk->top < *(chunk->top - 1)) 
		op(data, "sb");
	partition_b_gt_rrb(data, chunk, rb_cnt);
	return (pa_cnt);
}

static size_t	partition_b_gt_lastchunk(t_data *data, t_chunk *chunk, int div)
{
	size_t	pa_cnt;

	pa_cnt = 0;
	while(find_gt(chunk->top - chunk->size + 1, chunk->size, div) != -1)
	{
		if (*chunk->top > div)
		{
			op(data, "pa");
			++pa_cnt;
			--chunk->top;
			--chunk->size;
		}
		else if (*(chunk->top - chunk->size + 1) > div)
			op(data, "rrb");
		else
			op(data, "rb");
	}
	return (pa_cnt);
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
	int		mid;

	mid = nth_element_copy(data, chunk->top - chunk->size + 1,
			chunk->size, chunk->size / 2);
	if (!is_lastchunk)
		pa_cnt = partition_b_gt_basic(data, chunk, mid);
	else
		pa_cnt = partition_b_gt_lastchunk(data, chunk, mid);
	return (pa_cnt);
}
