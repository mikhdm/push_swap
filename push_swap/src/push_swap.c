/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:11:10 by rmander           #+#    #+#             */
/*   Updated: 2021/08/23 04:55:11 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "error.h"
#include "push_swap.h"
#include "stack.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define NC "\033[0m"

/*
* push_swap23 - push_swap machinery for size = 2 or 3.
*/
static void	push_swap23(t_data *data)
{
	const size_t	imid = 1;
	size_t			ind;

	if (issorted(data->a->data, data->a->size, FALSE))
		return ;
	if (data->a->size == 2)
	{
		op(data, "sa");
		return ;
	}
	while (!issorted(data->a->data, data->a->size, FALSE))
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

	if (issorted(data->a->data, data->a->size, FALSE))
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


static void debug_showsize(void *content)
{
	t_chunk *ch;

	ch = (t_chunk *)content;
	printf("--\nchunk top: %p\n", ch->top); 
	printf("chunk size: %zu\n--\n", ch->size);
}


static void	debug(t_stack *stack, char *color)
{
	size_t	i;

	i = stack->capacity;
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

static t_chunk	*lstadd_chunk(t_data *data)
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
* break stack A elements into chunks and put them into B
*/
static void	chunking_init(t_data *data)
{
	int 	mid;
	t_chunk	*chunk;

	chunk = NULL;
	while (!empty(data->a) && !issorted(data->a->data, data->a->size, FALSE))
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
	if (issorted(data->a->data, data->a->size, FALSE))
		return ;
	chunking_init(data);

	/* second part -- put data from chunks into A before chunk will be sorted in A. */
	/* size_t	rbc; */
	/* size_t	achunksize; */
	/* t_list	*newnode; */
	/* t_chunk	*newchunk; */
	/* node = data->chunks; */
	/* chunk = NULL; */

	/* newnode = NULL; */
	/* newchunk = NULL; */
	/* while (node) */
	/* { */
	/* 	chunk = (t_chunk *)node->content; */
	/* 	while (TRUE) */
	/* 	{ */
	/* 		if (mid_element_to(chunk->top + chunk->size - 1, chunk->size, &mid) == NULL) */
	/* 		{ */
	/* 			ft_lstclear(&chunks, free); */
	/* 			pexit(data, EXIT_FAILURE); */
	/* 		} */
	/* 		if (issorted(chunk->top + chunk->size - 1, chunk->size, TRUE)) */
	/* 		{ */
	/* 			while(chunk->size--) */
	/* 				op(data, "pa"); */
	/* 			chunk->top = NULL; */
	/* 		} */
	/* 		else if (chunk->size == 2) */
	/* 		{ */
	/* 			if (*chunk->top < *(chunk->top - 1)) */
	/* 				op(data, "sb"); */
	/* 			while (chunk->size--) */
	/* 				op(data, "pa"); */
	/* 			chunk->top = NULL; */
	/* 		} */
	/* 		else */
	/* 		{ */
	/* 			rbc = 0; */
	/* 			achunksize = 0; */
	/* 			while (find_gt(chunk->top + chunk->size - 1, chunk->size, mid) != -1) */
	/* 			{ */
	/* 				if (*chunk->top > mid) */
	/* 				{ */
	/* 					op(data, "pa"); */
	/* 					++achunksize; */
	/* 				} */
	/* 				else */
	/* 				{ */
	/* 					op(data, "ra"); */
	/* 					++rbc; */
	/* 				} */
	/* 				--chunk->top; */
	/* 				--chunk->size; */
	/* 			} */
	/* 			while (rbc--) */
	/* 			{ */
	/* 				op(data, "rra"); */ 
	/* 				++chunk->top; */
	/* 				++chunk->size; */
	/* 			} */


	/* 		} */
	/* 	} */
	/* 	node = node->next; */
	/* } */

	/* while (!empty(data->b)) */
	/* 	op(data, "pa"); */

	debug(data->a, issorted(data->a->data, data->a->size, FALSE) ? GREEN : RED);
	debug(data->b, issorted(data->b->data, data->b->size, FALSE) ? GREEN : RED);
	ft_lstiter(data->chunks, debug_showsize);
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