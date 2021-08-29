/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_lt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 03:06:04 by rmander           #+#    #+#             */
/*   Updated: 2021/08/23 03:06:44 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/types.h>

/*
* find_lt - returns index of first item less than value found
*			in values array
*/
ssize_t	find_lt(int const *values, size_t size, int value)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (values[i] < value)
			return ((ssize_t)i);
		++i;
	}
	return (-1);
}
