/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:11:10 by rmander           #+#    #+#             */
/*   Updated: 2021/08/26 00:34:35 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "error.h"
#include "push_swap.h"
#include "stack.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

/*
* push_swap23 - push_swap machinery for size = 2 or 3.
*/
static void	push_swap23(t_data *data)
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
* push_swap5 - push_swap machinery for size = 4 or 5.
*/
static void	push_swap45(t_data *data)
{
	const size_t	imid = data->a->size / 2;
	size_t			ind;
	int				value;

	if (issorted(data->a->data, data->a->size, DESC))
		return ;
	while (TRUE)
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
		if (data->a->size == 3)
			break ;
	}
	push_swap23(data);
	while (!empty(data->b))
		op(data, "pa");
}

void debug_showsize(void *content)
{
	t_chunk *ch;

	ch = (t_chunk *)content;
	printf("--\nchunk top: %p\n", ch->top); 
	printf("chunk size: %zu\n--\n", ch->size);
}

void	debug(t_stack *stack)
{
	size_t	i;
	char *color;

	i = stack->capacity;
	color = issorted(stack->data, stack->size, DESC) ? GREEN : RED;
	printf("\n-- DEBUG --\n\n");
	while (i > 0)
	{
		if (i > stack->size)
			printf("%s|%12s|%s\n", color, "", NC);
		else
			printf("%s|%12d|%s (%p)\n", color, stack->data[i - 1], NC, &stack->data[i - 1]);
		--i;
	}
	printf("capacity: %zu\n", stack->capacity);
	printf("size: %zu\n", stack->size);
	if (stack->top)
		printf("top: %d (%p)\n", *stack->top, stack->top);
	else
		printf("top: null\n");
	printf("\n-- END --\n\n");
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

void	minisort_a(t_data *data)
{
	/* indexify */
	int	*copy;
	size_t	i;
	
	if(!(alloca_to((void **)&copy, sizeof(int) * data->a->size)))
		pexit(data, EXIT_FAILURE);
	ft_memcpy(copy, data->a->data, sizeof(int) * data->a->size); 
	ft_qsort(copy, 0, data->a->size);
	i = 0;
	while (i < data->a->size)
	{
		data->a->data[i] = ft_linsearch(copy, (int)data->a->size, data->a->data[i]); 
		++i;
	}

	/* radix sort for 0 1 buckets. A - backet for 1, B - bucket for 0 */
	/* values here are lower than actual (saved in a copy) */
	/* because lower values will output less instructions */
	int 	max;
	int		nbits;
	int		b;
	size_t	k;
	int		value;
	size_t	pbc;
	size_t	size;

	max = data->a->data[ft_max(data->a->data, data->a->size)];
	size = data->a->size; 
	nbits = 0;
	while ((max >> nbits) != 0)
		++nbits;
	b = 0;
	while (b < nbits)
	{
		k = 0;
		pbc = 0;
		while (k < size)
		{
			value = *data->a->top >> b;
			if ((value & 1) == 1) 
				op(data, "ra");
			else
			{
				op(data, "pb");
				++pbc;
			}
			++k;
		}
		while (pbc--)
			op(data, "pa");
		++b;
	}
	i = 0;

	/* at this point stack A is sorted. */
	/* because algorithms works with indices and not actual values 
	 * we can simply copy sorted array in descending order into stack A. */
	while (i < data->a->size)
	{
		data->a->data[i] = copy[data->a->size - i - 1];
		++i;
	}
	free(copy);
}

/*
* break stack A elements into chunks and put them into B
*/
static void	chunking_initial(t_data *data)
{
	int 	mid;
	t_chunk	*chunk;

	chunk = NULL;
	while (!empty(data->a) && !issorted(data->a->data, data->a->size, DESC))
	{
		chunk = lstadd_chunk(data);
		mid = nth_element_copy(data, data->a->data, data->a->size,
				data->a->size / 3);
		while (find_lt(data->a->data, data->a->size, mid) != -1)
		{
			if (*data->a->top < mid)
			{
				op(data, "pb");
				chunk->size++;
			}
			else if (*data->a->data < mid)
				op(data, "rra");
			else
				op(data, "ra");
		}
		chunk->top = data->b->top;
		if (data->a->size <= 3)
			push_swap23(data);
	}
}

/*
* push_swap_g - push_swap generic machinery for cases when size > 5.
*/
static void push_swap_g(t_data *data)
{
	t_chunk	a_chunk;
	t_chunk	*b_chunk;
	t_list	*node;
	int		*bottom;
	size_t	sz;

	if (issorted(data->a->data, data->a->size, DESC))
		return ;
	chunking_initial(data);

	/* debug(data->a); */
	/* debug(data->b); */
	/* ft_lstiter(data->chunks, debug_showsize); */
	/* exit(0); */

	a_chunk = (t_chunk){.top = NULL, .size = 0};
	b_chunk = NULL;
	bottom = NULL;
	node = data->chunks;
	while (node)
	{
		b_chunk = (t_chunk *)node->content;
		if (!b_chunk->top)
		{
			node = node->next;
			continue ;
		}
		bottom = b_chunk->top - b_chunk->size + 1;
		if (issorted(bottom, b_chunk->size, ASC))
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
		if (b_chunk->size == 3)
			if (ft_min(bottom, b_chunk->size) == 0)
			{
				op(data, "sb");
				continue ;
			}
		sz = partition_b_gt(data, b_chunk);
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
void	push_swap(t_data *data)
{
	if (data->a->size == 2 || data->a->size == 3)
		push_swap23(data);
	else if (data->a->size == 4 || data->a->size == 5)
		push_swap45(data);
	else
		push_swap_g(data);
}