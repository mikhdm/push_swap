/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 23:08:41 by rmander           #+#    #+#             */
/*   Updated: 2021/07/31 01:04:22 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <limits.h>


ssize_t	max(t_stack *stack)
{
	ssize_t i;
	ssize_t imax;
	ssize_t *data;

	i = 0;
	imax = i;
	data = stack->data;
	while (++i < stack->size)
		if (data[i] > data[imax])
			imax = i;
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		/* ERROR */
	}
	return (0);
}
