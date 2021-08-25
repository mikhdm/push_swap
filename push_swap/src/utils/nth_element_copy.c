/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nth_element_copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 04:41:24 by rmander           #+#    #+#             */
/*   Updated: 2021/08/25 17:03:46 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "utils.h"
#include <stdlib.h>

/* 
* Allocate cache and copy current chunk to find nth element. 
* Mandatory due to partition operation of nth_element work and swaps in-place
* to save actual values unchanged.
*/
int	nth_element_copy(void *data, int *values, size_t size, size_t ind)
{
	int	*cache;
	int	mid;

	cache = NULL;
	if (!alloca_to((void **)&cache, sizeof(int) * size))
		pexit(data, EXIT_FAILURE);
	ft_memcpy(cache, values, sizeof(int) * size);
	mid = nth_element(cache, size, ind);
	free(cache);
	return (mid);
}
