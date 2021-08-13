/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 00:35:24 by rmander           #+#    #+#             */
/*   Updated: 2021/08/13 23:14:37 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "utils.h"
#include <stdlib.h>

static	void	setup(t_stack *s, int *values, size_t size)
{
	size_t	i;

	i = 0;
	s->top = NULL;
	s->bottom = NULL;
	s->size = 0;
	if (values)
	{
		while (i < size)
		{
			s->data[i] = values[size - i - 1];
			++i;
		}
		s->size = size;
		s->top = &s->data[s->size - 1];
		s->bottom = s->data;
	}
}

t_stack	*build(int *values, size_t size)
{
	t_stack	*s;

	s = NULL;
	if (!alloca_to((void **)&s, sizeof(t_stack)))
		return (NULL);
	if (!alloca_to((void **)&s->data, sizeof(int) * size))
	{
		free(s);
		return (NULL);
	}
	ft_memset(s->data, 0, sizeof(int) * size);
	setup(s, values, size);
	return (s);
}

short int	empty(t_stack *stack)
{
	if (stack->top)
		return (TRUE);
	return (FALSE);
}

short int	full(t_stack *stack)
{
	if (stack->top == &stack->data[stack->size - 1]
		&& stack->bottom == stack->data)
		return (TRUE);
	return (FALSE);
}

int	*pop(t_stack *stack)
{
	int	*value;

	value = stack->top;
	if (!value)
		return (NULL);
	if (stack->size == 1)
	{
		stack->top = NULL;
		stack->bottom = NULL;
	}
	else
		stack->top--;
	--stack->size;
	return (value);
}

int	*push(t_stack *stack, int value)
{
	if (full(stack))
		return (NULL);
	if (empty(stack))
	{
		stack->top = stack->data;
		stack->bottom = stack->data;
	}
	else
		++stack->top;
	*(stack->top) = value;
	return (stack->top);
}

//int push_bottom(t_stack *stack, int value)
//{
//
//}
//
//int pop_bottom(t_stack *stack, int value)
//{
//
//}