/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 09:03:32 by rmander           #+#    #+#             */
/*   Updated: 2021/08/29 09:03:58 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stddef.h>

size_t	ft_lstsize(t_list *lst)
{
	size_t	size;

	size = 0;
	while (lst)
	{
		++size;
		lst = lst->next;
	}
	return (size);
}
