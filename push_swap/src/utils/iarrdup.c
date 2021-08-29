/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iarrdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 08:46:16 by rmander           #+#    #+#             */
/*   Updated: 2021/08/29 18:58:24 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stddef.h>

int	*iarrdup(int *array, size_t	size)
{
	int	*copy;

	copy = NULL;
	if (!alloca_to((void **)&copy, sizeof(int) * size))
		return (NULL);
	ft_memcpy(copy, array, sizeof(int) * size);
	return (copy);
}
