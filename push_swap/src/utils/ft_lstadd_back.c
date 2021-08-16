/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 04:51:44 by rmander           #+#    #+#             */
/*   Updated: 2021/08/16 20:12:54 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*prev;
	t_list	*curr;

	prev = *lst;
	curr = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (curr)
	{
		prev = curr;
		curr = curr->next;
	}
	prev->next = new;
}
