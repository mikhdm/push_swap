/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 03:31:51 by rmander           #+#    #+#             */
/*   Updated: 2021/08/25 04:08:45 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_linsearch(int *values, int size, int value)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (values[i] == value)
			return (i);
		++i;
	}
	return (-1);
}
