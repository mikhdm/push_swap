/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 00:32:41 by rmander           #+#    #+#             */
/*   Updated: 2021/08/15 17:58:52 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

#include <stddef.h>

/*
* size - actual capacity of the array; 
* data - pointer of the data array;
* top - start of the array (end of the array by default);
* bottom - bottom of the stack (begin of the array by default);
*/
typedef struct s_stack
{
	int			*data;
	int			*top;
	size_t		size;
	size_t		capacity;
}	t_stack;

typedef struct s_data
{
	char	**ops;
	t_stack *a;
	t_stack *b;
}	t_data;

t_stack		*build(int *values, size_t size);
short int	empty(t_stack *stack);
short int	full(t_stack *stack);
int			*pop_back(t_stack *stack);
/* int			*pop_front(t_stack *stack); */
int			*push_back(t_stack* stack, int value);
/* int			*push_front(t_stack* stack, int value); */

#endif
