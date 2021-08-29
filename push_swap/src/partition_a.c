/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 23:43:12 by rmander           #+#    #+#             */
/*   Updated: 2021/08/29 23:48:05 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"
#include "stack.h"
#include "op.h"

static	void	partition_a_lt_rra(t_data *data, t_chunk *chunk, size_t ra_cnt)
{
	while (ra_cnt--)
	{
		op(data, "rra");
		++chunk->size;
	}
}

static size_t	partition_a_lt_basic(t_data *data, t_chunk *chunk, int div)
{
	size_t	pb_cnt;
	size_t	ra_cnt;

	pb_cnt = 0;
	ra_cnt = 0;
	while (find_lt(chunk->top - chunk->size + 1, chunk->size, div) != -1)
	{
		if (*chunk->top < div)
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
	if (chunk->size >= 2 && *chunk->top > *(chunk->top - 1))
		op(data, "sa");
	partition_a_lt_rra(data, chunk, ra_cnt);
	return (pb_cnt);
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
	int		mid;

	pb_cnt = 0;
	mid = nth_element_copy(data, chunk->top - chunk->size + 1,
						   chunk->size, chunk->size / 2);
	pb_cnt = partition_a_lt_basic(data, chunk, mid);
	return (pb_cnt);
}