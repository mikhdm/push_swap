/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 22:34:50 by rmander           #+#    #+#             */
/*   Updated: 2021/08/16 22:53:46 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_max(int *values, size_t size)
{
	size_t	i;
	size_t	imax;

	i = 1;
	imax = 0;
	while (i < size)
	{
		if (values[i] > values[imax])
			imax = i;
		++i;
	}
	return (imax);
}
