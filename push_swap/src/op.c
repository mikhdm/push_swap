/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 04:43:18 by rmander           #+#    #+#             */
/*   Updated: 2021/08/16 18:36:50 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "stack.h"

void	sx(t_data *data, char *cmd)
{
	if (ft_strcmp(cmd, "sa") == 0)
	{
		if (!empty(data->a) && data->a->size > 1)
			swap(&data->a->data[data->a->size - 1], &data->a->data[data->a->size - 2]); 
	}
	else if (ft_strcmp(cmd, "sb") == 0)
	{
		if (!empty(data->b) && data->b->size > 1)
			swap(&data->b->data[data->b->size - 1], &data->b->data[data->b->size - 2]);
	}
	else if (ft_strcmp(cmd, "ss") == 0)
	{
		sx(data, "sa");
		sx(data, "sb");
	}
}

void	px(t_data *data, char *cmd)
{
	if (ft_strcmp(cmd, "pa") == 0)
	{
		if (!empty(data->b))
			push_back(data->a, *pop_back(data->b));
	}
	else if (ft_strcmp(cmd, "pb") == 0)
	{
		if (!empty(data->a))
			push_back(data->b, *pop_back(data->a));
	}
}

void	rx(t_data *data, char *cmd)
{
	if (ft_strcmp(cmd, "ra") == 0)
	{
		if (!empty(data->a))
			push_front(data->a, *pop_back(data->a));
	}
	else if (ft_strcmp(cmd, "rb") == 0)
	{
		if (!empty(data->b))
			push_front(data->b, *pop_back(data->b));
	}
	else if (ft_strcmp(cmd, "rr") == 0)
	{
		rx(data, "ra");
		rx(data, "rb");
	}
}

void	rrx(t_data *data, char *cmd)
{
	if (ft_strcmp(cmd, "rra") == 0)
	{
		if (!empty(data->a))
			push_back(data->a, *pop_front(data->a));
	}
	else if (ft_strcmp(cmd, "rrb") == 0)
	{
		if (!empty(data->b))
			push_back(data->b, *pop_front(data->b));
	}
	else if (ft_strcmp(cmd, "rrr") == 0)
	{
		rrx(data, "rra");
		rrx(data, "rrb");
	}
}

void	op(t_data *data, char *cmd)
{
	if (ft_strcmp(cmd, "pa") == 0
		|| ft_strcmp(cmd, "pb") == 0)
		px(data, cmd);
	else if (ft_strcmp(cmd, "sa") == 0
			|| ft_strcmp(cmd, "sb") == 0
			|| ft_strcmp(cmd, "ss") == 0)
		sx(data, cmd);
	else if (ft_strcmp(cmd, "ra") == 0
			|| ft_strcmp(cmd, "rb") == 0
			|| ft_strcmp(cmd, "rr") == 0)
		rx(data, cmd);
	else if (ft_strcmp(cmd, "rra") == 0
			|| ft_strcmp(cmd, "rrb") == 0
			|| ft_strcmp(cmd, "rrr") == 0)
		rrx(data, cmd);
}
