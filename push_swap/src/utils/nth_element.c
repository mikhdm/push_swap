/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nth_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 17:55:49 by rmander           #+#    #+#             */
/*   Updated: 2021/08/30 00:23:52 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
* Hoar partition
*/
static size_t	partition(int *values, size_t l, size_t r)
{
	size_t	pivot;
	size_t	result;

	result = l;
	pivot = r;
	while (l < r)
	{
		if (values[l] <= values[pivot])
		{
			swap(&values[result], &values[l]);
			++result;
		}
		++l;
	}
	swap(&values[pivot], &values[result]);
	return (result);
}

/*
 * nth_element - returns value from sorted values at k
 */
int	nth_element(int *values, size_t size, size_t k)
{
	size_t	l;
	size_t	r;
	size_t	m;

	l = 0;
	r = size - 1;
	while (TRUE)
	{
		m = partition(values, l, r);
		if (k == m)
			break ;
		else if (k > m)
			l = m + 1;
		else
			r = m - 1;
	}
	return (values[m]);
}
