/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 03:37:34 by rmander           #+#    #+#             */
/*   Updated: 2021/08/25 03:28:52 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "utils.h"
#include <stdlib.h>

static	void	setup(t_stack *s, int *values, size_t capacity)
{
	size_t	i;

	i = 0;
	s->top = NULL;
	s->size = 0;
	s->capacity = capacity;
	if (values)
	{
		while (i < capacity)
		{
			s->data[i] = values[capacity - i - 1];
			++i;
		}
		s->size = capacity;
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

short int	empty(t_stack *stack)
{
	if (stack->top)
		return (FALSE);
	return (TRUE);
}

short int	full(t_stack *stack)
{
	if (stack->top == &stack->data[stack->capacity - 1])
		return (TRUE);
	return (FALSE);
}
