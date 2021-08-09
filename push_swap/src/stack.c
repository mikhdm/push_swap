/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 00:35:24 by rmander           #+#    #+#             */
/*   Updated: 2021/08/09 05:51:02 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "utils.h"
#include "error.h"
#include <stdlib.h>

static void	setup(t_stack *s, int *values, size_t size)
{
	size_t	i;

	i = 0;
	s->top = s->data;
	s->bottom = s->data;
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

int	*top(t_stack *stack)
{
	if (!empty(stack))
		return (stack->top);
	return (NULL);
}

short int	empty(t_stack *stack)
{
	if (stack->top == stack->bottom)
		return (TRUE);
	return (FALSE);
}

size_t	size(t_stack *stack)
{
	return (stack->size);
}

short int	full(t_stack *stack)
{
	if (stack->top == &stack->data[stack->size - 1]
		&& stack->bottom == stack->data)
		return (TRUE);
	return (FALSE);
}

/* size_t	pop(t_stack *stack) */
/* { */
/* 	ssize_t	value; */

/* 	value = top(s); */
/* 	*s->top = NULL; */
/* 	if (s->top == &s->data[s->capacity - 1]) */
/* 		return (value); */
/* 	s->top++; */
/* 	if (*s->top == EMPTY_VALUE) */
/* 		s->top = NULL; */
/* 	s->size--; */
/* 	return (value); */
/* } */

/* size_t push(t_stack *stack, ssize_t value) */
/* { */

/* } */
