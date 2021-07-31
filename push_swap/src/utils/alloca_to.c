/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloca_to.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:10:26 by rmander           #+#    #+#             */
/*   Updated: 2021/07/31 01:06:56 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

short int	alloca_to(void **ptr, size_t size)
{
	*ptr = malloc(size);
	if (!*ptr)
		return (FALSE);
	return (TRUE);
}
