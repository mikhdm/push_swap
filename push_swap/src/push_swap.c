/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:11:10 by rmander           #+#    #+#             */
/*   Updated: 2021/08/25 02:18:00 by rmander          ###   ########.fr       */
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

/* static	void	minisort_a(t_data *data) */
/* { */
/* 	size_t	ind; */
/* 	size_t	imid; */
/* 	int		value; */
/* 	size_t	pb_cnt; */
	
/* 	pb_cnt = 0; */
/* 	imid = data->a->size / 2; */
/* 	while (!issorted(data->a->data, data->a->size, DESC)) */
/* 	{ */
/* 		ind = ft_min(data->a->data, data->a->size); */ 
/* 		value = data->a->data[ind]; */
/* 		if (ind >= imid) */
/* 			while (*data->a->top != value) */
/* 				op(data, "ra"); */
/* 		else */
/* 			while (*data->a->top != value) */
/* 				op(data, "rra"); */
/* 		op(data, "pb"); */
/* 		++pb_cnt; */
/* 		if (data->a->size <= 3) */
/* 			push_swap23(data); */
/* 	} */
/* 	while (pb_cnt--) */
/* 		op(data, "pa"); */
/* } */

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
				data->a->size / 2);
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