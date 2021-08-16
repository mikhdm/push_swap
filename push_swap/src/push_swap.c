/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 16:11:10 by rmander           #+#    #+#             */
/*   Updated: 2021/08/16 19:57:47 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "stack.h"
#include "utils.h"

/*
*
* finale - function to check non-empty stack is sorted.
* empty stack is not considered sorted here to allow operations continue.
* issorted function checks from the pointer passed as an argument until size is reached.
* stack->data[0] is a bottom of the stack, that's why we should check in descending order.
*
*/
static short int	finale(t_stack *stack)
{
	if (empty(stack))
		return (FALSE);
	return (issorted(stack->data, stack->size, FALSE));
}

static void	push_swap3(t_data *data)
{
	while (!finale(data->a))
	{
		op(data, "pa");
	}
}

static void	push_swap5(t_data *data)
{
	while (!finale(data->a))
	{
		/* TODO */
	}
}

static void push_swap_all(t_data *data)
{
	while (!finale(data->a))
	{
		/* TODO */
	}
}

void	push_swap(t_data *data)
{
	if (data->a->size == 3)
		push_swap3(data);
	else if (data->a->size > 3 && data->a->size <= 5)
		push_swap5(data);
	else
		push_swap_all(data);
}
