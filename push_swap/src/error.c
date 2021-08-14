/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 19:52:25 by rmander           #+#    #+#             */
/*   Updated: 2021/08/14 21:08:51 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "stack.h"
#include <stdlib.h>
#include <unistd.h>

void	cleanup(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
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
}

void	pexit(void *ptr, int status)
{
	const char	*error = "Error\n";

	if (status == EXIT_FAILURE)
		write(STDERR_FILENO, error, ft_strlen(error)); 
	cleanup(ptr);
	exit(status);
}
