/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 22:31:29 by rmander           #+#    #+#             */
/*   Updated: 2021/08/16 22:53:49 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_min(int *values, size_t size)
{
	size_t	i;
	size_t	imin;

	i = 1;
	imin = 0;
	while (i < size)
	{
		if (values[i] < values[imin])
			imin = i;
		++i;
	}
	return (imin);
}
