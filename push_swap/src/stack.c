/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 00:35:24 by rmander           #+#    #+#             */
/*   Updated: 2021/08/19 17:01:27 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "utils.h"
#include <stddef.h>

int	*pop_back(t_stack *stack)
{
	int	*value;

	value = stack->top;
	if (!value)
		return (NULL);
	--stack->size;
	if (stack->size == 0)
		stack->top = NULL;
	else
		--stack->top;
	return (value);
}

int	*push_back(t_stack *stack, int value)
{
	if (full(stack))
		return (NULL);
	if (empty(stack))
		stack->top = stack->data;
	else
		++stack->top;
	*(stack->top) = value;
	++stack->size;
	return (stack->top);
}

int	*push_front(t_stack *stack, int value)
{
	size_t	i;

	if (full(stack))
		return (NULL);
	if (empty(stack))
		return (push_back(stack, value));
	i = stack->size;
	while (i > 0)
	{
		stack->data[i] = stack->data[i-1];
		--i;
	}
	stack->data[0] = value;
	stack->top = stack->data + stack->size;
	++stack->size;
	return (stack->top);
}

int	*pop_front(t_stack *stack)
{
	size_t	i;
	int		*value;
	int		popped;

	if (empty(stack))
		return (NULL);
	popped = stack->data[0];
	i = 1;
	while (i < stack->size)
	{
		stack->data[i - 1] = stack->data[i];
		++i;
	}
	stack->data[stack->size - 1] = popped;
	value = &stack->data[stack->size - 1];
	--stack->size;
	if (stack->size == 0)
		stack->top = NULL;
	else
		--stack->top;
	return (value);
}