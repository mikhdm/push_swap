/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:08:55 by rmander           #+#    #+#             */
/*   Updated: 2021/08/22 03:18:26 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "stack.h"

typedef struct s_chunk {
	size_t	size;
	int		*top;
}	t_chunk;

void	push_swap(t_data *data);

#endif
