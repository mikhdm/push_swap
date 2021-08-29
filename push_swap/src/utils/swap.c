/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 04:49:30 by rmander           #+#    #+#             */
/*   Updated: 2021/08/30 00:24:31 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	swap(int *l, int *r)
{
	int	tmp;

	tmp = *l;
	*l = *r;
	*r = tmp;
}
