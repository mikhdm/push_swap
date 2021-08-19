/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:11:10 by rmander           #+#    #+#             */
/*   Updated: 2021/08/19 23:18:28 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "error.h"
#include "stack.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

/*
* sorted - function to check non-empty stack is sorted.
* 			empty stack is not considered sorted here
* 			to allow operations continue,
* 			issorted function checks from the pointer passed
* 			as an argument until size is reached,
* 			stack->data[0] is a bottom of the stack,
* 			that's why we should check in descending order.
*/
static int	sorted(t_stack *stack)
{
	return (!empty(stack)
			&& issorted(stack->data, stack->size, FALSE));
}

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
	while (!sorted(data->a))
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
	const size_t	imid = data->a->capacity / 2;
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
/* static ssize_t	find_gt(int const *values, size_t size, int value) */
/* { */
/* 	size_t 	i; */

/* 	i = 0; */
/* 	while (i < size) */
/* 	{ */
/* 		if (values[i] > value) */
/* 			return ((ssize_t)i); */
/* 		++i; */
/* 	} */
/* 	return (-1); */
/* } */

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

/*
* push_swapg - push_swap machinery for cases when size > 5.
*/
static void push_swapg(t_data *data)
{
//	size_t	ind;
//	size_t	imid;
	/* int		value; */
	int 	mid;
	int 	*cache;
	/* int		count; */

	if (issorted(data->a->data, data->a->size, FALSE))
		return ;

	cache = NULL;
	if (!alloca_to((void **)&cache, sizeof(int) * data->a->capacity))
		pexit(data, EXIT_FAILURE);
	ft_memcpy(cache, data->a->data, sizeof(int) * data->a->capacity);
	mid = nth_element(cache, data->a->capacity, data->a->capacity / 2);

	while (find_lt(data->a->data, data->a->size, mid) != -1)
	{
		if (*data->a->top < mid)
			op(data, "pb");
		else if (*data->a->data < mid)
			op(data, "rra");
		else
			op(data, "ra");
	}

	size_t i;

	i = 0;
	while (i < data->b->size)
	{
		printf("%d\n", data->b->data[data->b->size - i - 1]);
		++i;
	}

	free(cache);
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
		push_swapg(data);
}