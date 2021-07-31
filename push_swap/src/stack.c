/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 00:35:24 by rmander           #+#    #+#             */
/*   Updated: 2021/07/31 04:05:03 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "utils.h"
#include <stdlib.h>
#include <limits.h>

void init(t_stack *s)
{
	s->size = 0;
	s->capacity = DEFAULT_CAPACITY;
	if (!alloca_to((void **)&s->data, sizeof(ssize_t) * DEFAULT_CAPACITY))
	{
		/* ERROR */ 
	}
	ft_memset(s->data, EMPTY_VALUE, sizeof(ssize_t) * DEFAULT_CAPACITY);
	s->top = NULL;
}

ssize_t	top(t_stack	*s)
{
	return (*s->top);
}

ssize_t	pop(t_stack *s)
{
	ssize_t	value;

	value = top(s);
	*s->top = EMPTY_VALUE;
	if (s->top == &s->data[s->capacity - 1])
		return (value);
	s->top++;
	if (*s->top == EMPTY_VALUE)
		s->top = NULL;
	s->size--;
	return (value);
}

ssize_t push(t_stack *s, ssize_t value)
{

}

ssize_t	size(t_stack *s)
{
	return (s->size);
}
