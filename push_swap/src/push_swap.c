/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:11:10 by rmander           #+#    #+#             */
/*   Updated: 2021/08/29 10:45:41 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "error.h"
#include "push_swap.h"
#include "stack.h"
#include "utils.h"
#include <stdlib.h>

/*
* @brief Machinery for size = 2 or 3.
*
* Takes data in a stack A and sorts them by hand.
*
* @param data Global state structure.
*
* @returns Nothing.
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
* @brief Machinery for size <= 5.
*
* Takes data in a stack A and sorts them by hand.
*
* @param data Global state structure.
*
* @returns Nothing.
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
* push_swap_g - push_swap generic machinery for cases when size > 5.
*/
static void push_swap_g(t_data *data, const double div)
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
 * push_swap - main algorithm which choose appropriate
 * 				function to call for sorting.
 * 				all algorithms consider assumptions that
 * 				all elements unique
 * 				and positive (after mapping elements to indices).
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