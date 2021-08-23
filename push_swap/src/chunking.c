/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 19:49:32 by rmander           #+#    #+#             */
/*   Updated: 2021/08/24 00:41:03 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "stack.h"
#include "utils.h"
#include "push_swap.h"

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
void	chunking_a_lt(t_data *data, t_chunk *chunk)
{
	size_t	sz;
	int		mid;
	int		*bottom;
	t_chunk	*b_chunk;

	b_chunk = NULL;
	bottom = chunk->top - chunk->size + 1;
	while(!issorted(bottom, chunk->size, DESC))
	{
		if (chunk->size == 2)
		{
				op(data, "sa");
				break ;
		}
		b_chunk = lstadd_chunk(data);
		mid = nth_element_copy(data, bottom, chunk->size, chunk->size / 2);
		sz = partition_a_lt(data, chunk, mid);
		b_chunk->top = data->b->top;
		b_chunk->size = sz;
	}
}
