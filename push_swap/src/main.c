/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 23:08:41 by rmander           #+#    #+#             */
/*   Updated: 2021/08/03 03:03:58 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "error.h"
#include "utils.h"
#include <stddef.h>
#include <limits.h>
#include <stdlib.h>

int	valid(size_t argc, char **argv)
{
	char	*digit;
	size_t	i;
	ssize_t	value;

	i = 0;
	digit = NULL;
	value = 0;
	while (i < argc)
	{
		digit = argv[i];
		if (*digit == '-' || *digit == '+')
			++digit;
		if (!*digit)
			return (FALSE);
		while(*digit)
		{
			if (!ft_isdigit(*digit))
				return (FALSE);
			++digit;
		}
		++i;
	}
	return (TRUE);
}

int main(int argc, char **argv)
{
	t_data	data;
	char	**strs;

	strs = NULL;
	data = (t_data){.a = NULL, .b = NULL, .ops = NULL};
	if (argc == 1)
		pexit(NULL, EXIT_FAILURE);
	if (argc == 2)
	{
		strs = ft_splitf(argv[1], ft_isspace);
		if (!strs)
			pexit(NULL, EXIT_FAILURE);
		if (!valid(ft_strslen(strs), strs))
		{
			free(strs);
			pexit(NULL, EXIT_FAILURE);
		}
	}

	--argc;
	if (!valid(argc, argv))
		pexit(NULL, EXIT_FAILURE);
	data.a = new(argc);
	if (!data.a)
		pexit(NULL, EXIT_FAILURE);
	data.b = new(argc);
	if (!data.b)
		pexit(&data, EXIT_FAILURE);
	return (0);
}
