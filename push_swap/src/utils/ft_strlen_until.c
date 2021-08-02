/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_until.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 23:25:34 by rmander           #+#    #+#             */
/*   Updated: 2021/08/02 23:33:12 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen_until(const char *s, const char sym)
{
	size_t	i;

	i = 0;
	while (*s && (*s != sym))
	{
		++i;
		++s;
	}
	return (i);
}
