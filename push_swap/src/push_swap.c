/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:11:10 by rmander           #+#    #+#             */
/*   Updated: 2021/08/30 00:51:42 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "error.h"
#include "push_swap.h"
#include "stack.h"
#include "utils.h"
#include <stdlib.h>

/*
* @brief Routine for size = 2 or 3.
*
* Takes data in a stack A and sorts them by hand.
*
* @param data Global state structure.
*
* @return Nothing.
*/
static	void	push_swap23(t_data *data)
{
	const size_t	imid = 1;
	size_t			ind;

	if (issorted(data->a->data, data->a->size, DESC))
		return ;
	if (data->a->size == 2)
	{
		op(data, "sa");
		return ;
	}
	while (!issorted(data->a->data, data->a->size, DESC))
	{
		ind = ft_max(data->a->data, data->a->size);
		if (ind > imid)
			op(data, "ra");
		if (ind == imid)
			op(data, "rra");
		if (*data->a->top > *(data->a->top - 1))
			op(data, "sa");
	}
}

/*
* @brief Routine for size <= 5.
*
* Takes data in a stack A and sorts them by hand.
*
* @param data Global state structure.
*
* @return Nothing.
*/
void	push_swap45(t_data *data)
{
	const size_t	imid = data->a->size / 2;
	size_t			ind;
	int				value;
	size_t			pb_cnt;

	if (issorted(data->a->data, data->a->size, DESC))
		return ;
	pb_cnt = 0;
	while (data->a->size >= 3)
	{
		ind = ft_min(data->a->data, data->a->size);
		value = data->a->data[ind];
		if (ind >= imid)
			while (*data->a->top != value)
				op(data, "ra");
		else
			while (*data->a->top != value)
				op(data, "rra");
		op(data, "pb");
		++pb_cnt;
	}
	push_swap23(data);
	while (pb_cnt--)
		op(data, "pa");
}

t_chunk	*lstadd_chunk(t_data *data)
{
	t_chunk	*chunk;
	t_list	*node;

	chunk = NULL;
	node = NULL;
	if (!alloca_to((void **)&chunk, sizeof(t_chunk)))
		pexit(data, EXIT_FAILURE);
	chunk->size = 0;
	chunk->top = NULL;
	node = ft_lstnew(chunk);
	if (!node)
	{
		free(chunk);
		pexit(data, EXIT_FAILURE);
	}
	ft_lstadd_front(&data->chunks, node);
	return (chunk);
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
static	void	push_swap_g(t_data *data, const double div)
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
		is_lastchunk = FALSE;
		if (!node->next)
			is_lastchunk = TRUE;
		b_chunk = (t_chunk *)node->content;
		if (!b_chunk->top)
		{
			node = node->next;
			continue ;
		}
		if (issorted(b_chunk->top - b_chunk->size + 1, b_chunk->size, ASC))
		{
			while (b_chunk->size--)
				op(data, "pa");
			b_chunk->top = NULL;
			b_chunk->size = 0;
			node = node->next;
			continue ;
		}
		if (b_chunk->size == 2)
		{
			if (*b_chunk->top < *(b_chunk->top - 1))
				op(data, "sb");
			continue ;
		}
		sz = partition_b_gt(data, b_chunk, is_lastchunk);
		a_chunk.size = sz;
		a_chunk.top = data->a->top;
		chunking_a_lt(data, &a_chunk);
		node = data->chunks;
	}
}

/*
* @brief Routine for choosing algorithm depending on input size.
*
* @param data Global state structure.
* @param div Partition divider for chunking_initial routine.
*
* @return Nothing.
*/
void	push_swap(t_data *data, const double div)
{
	if (data->a->size == 2 || data->a->size == 3)
		push_swap23(data);
	else if (data->a->size == 4 || data->a->size == 5)
		push_swap45(data);
	else
		push_swap_g(data, div);
}
