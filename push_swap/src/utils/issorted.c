/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   issorted.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 04:27:29 by rmander           #+#    #+#             */
/*   Updated: 2021/08/30 00:22:58 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
* asc = TRUE -- ascending
* asc = FALSE -- descending
*/
short int	issorted(int *values, size_t size, short int asc)
{
	size_t		i;
	short int	is;

	i = 1;
	is = TRUE;
	if (!values || (size == 1))
		return (is);
	while (i < size)
	{
		if ((asc && (values[i - 1] > values[i]))
			|| (!asc && (values[i - 1] < values[i])))
		{
			is = FALSE;
			break ;
		}
		++i;
	}
	return (is);
}
