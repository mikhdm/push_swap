/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 01:21:15 by rmander           #+#    #+#             */
/*   Updated: 2021/08/02 21:31:14 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>

void	*ft_memset(void *b, int c, size_t len)
{
	void	*s;

	s = b;
	while (len--)
		*(unsigned char *)b++ = (unsigned char)c;
	return (s);
}
