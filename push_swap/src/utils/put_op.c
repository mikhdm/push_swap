/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 11:04:14 by rmander           #+#    #+#             */
/*   Updated: 2021/08/29 11:04:35 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>

void	put_op(void *op)
{
	write(STDOUT_FILENO, op, ft_strlen_until((const char *)op, '\0'));
	write(STDOUT_FILENO, "\n", 1);
}
