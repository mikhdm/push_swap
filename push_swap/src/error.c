/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:52:25 by rmander           #+#    #+#             */
/*   Updated: 2021/08/02 23:33:36 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "stack.h"
#include <stdlib.h>
#include <unistd.h>

void	pexit(t_data *data, int status)
{
	const char	*error = "Error\n";

	if (status == EXIT_FAILURE)
		write(STDERR_FILENO, error, ft_strlen(error)); 
	if (data)
	{
		if (data->a)
		{
			if (data->a->data)
				free(data->a->data);
			free(data->a);
		}
		if (data->b)
		{
			if (data->b->data)
				free(data->b->data);
			free(data->b);
		}
		if (data->ops)
			free(data->ops);
	}
	exit(status);
}
