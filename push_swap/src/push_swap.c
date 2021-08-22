/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:11:10 by rmander           #+#    #+#             */
/*   Updated: 2021/08/22 05:03:32 by rmander          ###   ########.fr       */
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

/*
* find_lt - returns index of first item less than value found
*			in values array
*/
static ssize_t	find_lt(int const *values, size_t size, int value)
{
	size_t 	i;

	i = 0;
	while (i < size)
	{
		if (values[i] < value)
			return ((ssize_t)i);
		++i;
	}
	return (-1);
}

/*
* find_gt - returns index of first item greater than or equal value found
*			in values array
*/
static ssize_t	find_gt(int const *values, size_t size, int value)
{
	size_t 	i;

	i = 0;
	while (i < size)
	{
		if (values[i] > value)
			return ((ssize_t)i);
		++i;
	}
	return (-1);
}

/*
* find_leq - returns index of first less than or equal value found
*			in values array
*/
/* static ssize_t	find_leq(int const *values, size_t size, int value) */
/* { */
/* 	size_t 	i; */

/* 	i = 0; */
/* 	while (i < size) */
/* 	{ */
/* 		if (values[i] <= value) */
/* 			return ((ssize_t)i); */
/* 		++i; */
/* 	} */
/* 	return (-1); */
/* } */

/*
* find_geq - returns index of first greater than or equal value found
*			in values array
*/
/* static ssize_t	find_geq(int const *values, size_t size, int value) */
/* { */
/* 	size_t 	i; */

/* 	i = 0; */
/* 	while (i < size) */
/* 	{ */
/* 		if (values[i] >= value) */
/* 			return ((ssize_t)i); */
/* 		++i; */
/* 	} */
/* 	return (-1); */
/* } */

static void debug_showsize(void *content)
{
	t_chunk *ch;

	ch = (t_chunk *)content;
	printf("--\nchunk top: %p\n", ch->top); 
	printf("chunk size: %zu\n--\n", ch->size);
}

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define NC "\033[0m"

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


/* 
* Allocate cache and copy current chunk to find mid element. 
* Mandatory due to partition operation of nth_element work and swaps in-place
* to save actual chunk unchanged.
*/
static int	*mid_element_to(int *values, size_t size, int *to)
{
	int *cache;

	cache = NULL;
	if (!alloca_to((void **)&cache, sizeof(int) * size))
		return (NULL);
	ft_memcpy(cache, values, sizeof(int) * size);
	/* find mid value from current chunk */
	*to = nth_element(cache, size, size / 2);
	free(cache);
	return (to);
}

/*
* push_swap_g - push_swap generic machinery for cases when size > 5.
*/
static void push_swap_g(t_data *data)
{
	int 	mid;
	t_list	*chunks;
	t_list	*node;
	t_chunk	*chunk;

	chunks = NULL;
	node = NULL;
	if (issorted(data->a->data, data->a->size, FALSE))
		return ;

	/* first part of machinery - break stack A elements into chunks and
	 * put them into B */
	while (!empty(data->a) && !issorted(data->a->data, data->a->size, FALSE))
	{
		chunk = NULL;
		if (!alloca_to((void **)&chunk, sizeof(t_chunk)))
		{
			ft_lstclear(&chunks, free);
			pexit(data, EXIT_FAILURE);
		}
		chunk->size = 0;
		chunk->top = NULL;
		node = ft_lstnew(chunk);	
		if (!node)
		{
			free(chunk);
			ft_lstclear(&chunks, free);
			pexit(data, EXIT_FAILURE);
		}
		ft_lstadd_back(&chunks, node);
		if (mid_element_to(data->a->data, data->a->size, &mid) == NULL)
		{
			ft_lstclear(&chunks, free);
			pexit(data, EXIT_FAILURE);
		}
		/* copy chunk from A into B */
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

	/* second part -- put data from chunks into A before chunk will be sorted in A. */
	size_t	rb_cnt;
	node = chunks;
	chunk = NULL;
	while (node)
	{
		chunk = (t_chunk *)node->content;
		if (issorted(chunk->top + chunk->size - 1, chunk->size, TRUE))
		{
			while(chunk->size--)
				op(data, "pa");
			chunk->top = NULL;
		}
		else if (chunk->size == 2)
		{
			if (*chunk->top < *(chunk->top - 1))
				op(data, "sb");
			while(chunk->size--)
				op(data, "pa");
			chunk->top = NULL;
		}
		else
		{
			rb_cnt = 0;
			if (mid_element_to(chunk->top + chunk->size - 1, chunk->size, &mid) == NULL)
			{
				ft_lstclear(&chunks, free);
				pexit(data, EXIT_FAILURE);
			}
			while (find_gt(chunk->top + chunk->size - 1, chunk->size, mid) != -1)
			{
				if (*chunk->top > mid)
				{
					op(data, "pa");
				}
				else
				{
					op(data, "rb");
					++rb_cnt;
				}
				--chunk->top;
				--chunk->size;
			}
			while (rb_cnt--)
			{
				op(data, "rrb");
				++chunk->top;
				++chunk->size;
			}
		}
		node = node->next;
	}

	while (!empty(data->b))
		op(data, "pa");

	debug(data->a, issorted(data->a->data, data->a->size, FALSE) ? GREEN : RED);
	debug(data->b, issorted(data->b->data, data->b->size, FALSE) ? GREEN : RED);

	ft_lstiter(chunks, debug_showsize);
	ft_lstclear(&chunks, free); 
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