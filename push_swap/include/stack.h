/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 00:32:41 by rmander           #+#    #+#             */
/*   Updated: 2021/07/31 04:05:05 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <sys/types.h>

# define DEFAULT_CAPACITY	10
# define EMPTY_VALUE		SSIZE_MAX

typedef struct t_stack {
	ssize_t *top;
	ssize_t	size;
	ssize_t	capacity;
	ssize_t	*data;
}	t_stack;

void		init(t_stack *s);
ssize_t		top(t_stack	*s);
ssize_t		pop(t_stack *s);
ssize_t		push(t_stack *s, ssize_t value);
ssize_t		size(t_stack *s);
short int	empty(t_stack *s);

#endif
