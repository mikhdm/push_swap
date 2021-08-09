/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 00:32:41 by rmander           #+#    #+#             */
/*   Updated: 2021/08/09 05:35:02 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

#include <stddef.h>

/*
* size - actual capacity of the array; 
* data - poiter of the data array;
* top - start of the array (end of the array by default);
* bottom - bottom of the stack (begin of the array by default);
*/
typedef struct s_stack
{
	size_t	size;
	int		*data;
	int		*top;
	int		*bottom;
}	t_stack;

typedef struct s_data
{
	t_stack *a;
	t_stack *b;
	char	**ops;
}	t_data;

t_stack		*build(int *values, size_t size);
size_t		size(t_stack *stack);
int			*top(t_stack *stack);
short int	empty(t_stack *stack);
short int	full(t_stack *stack);

/* int			pop(t_stack *stack); */
/* int			push(t_data *data, t_stack *stack, int value); */
/* void		rotate(t_data *data, t_stack *stack); */

#endif
