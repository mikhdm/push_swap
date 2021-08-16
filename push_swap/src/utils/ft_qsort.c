/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 17:01:03 by rmander           #+#    #+#             */
/*   Updated: 2021/08/16 04:49:46 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stddef.h>

/*
*
* Hoar partition
*
*/
static size_t	partition(int *values, size_t l, size_t r)
{
	size_t pivot;
	size_t result;
	
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

int	*ft_qsort(int *values, size_t l, size_t r)
{
	size_t	ipivot;

	if (l < r)
	{
		ipivot = partition(values, l, r - 1);
		ft_qsort(values, l, ipivot);
		ft_qsort(values, ipivot + 1, r);
	}
	return (values);
}
