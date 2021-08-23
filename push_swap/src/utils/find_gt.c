/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_gt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 03:04:57 by rmander           #+#    #+#             */
/*   Updated: 2021/08/23 03:05:36 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/types.h>

/*
* find_gt - returns index of first item greater than or equal value found
*			in values array
*/
ssize_t	find_gt(int const *values, size_t size, int value)
{
	size_t 	i;

	i = 0;
	while (i < size)
	{
		if (values[i] > value)
			return ((ssize_t)i);
		++i;
	}
	return (-1);
}
