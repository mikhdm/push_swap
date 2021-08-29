/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 08:51:39 by rmander           #+#    #+#             */
/*   Updated: 2021/08/29 09:01:14 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "error.h"
#include <stdlib.h>
#include <limits.h>

int	duplicated(int *values, size_t size)
{
	size_t		i;
	int			*sorted;
	short int	is;

	sorted = NULL;
	is = FALSE;
	i = 1;
	if (!alloca_to((void **)&sorted, sizeof(int) * size))
	{
		free(values);
		pexit(NULL, EXIT_FAILURE);
	}
	ft_memcpy(sorted, values, sizeof(int) * size);
	sorted = ft_qsort(sorted, 0, size);
	while (i < size)
	{
		if (sorted[i - 1] == sorted[i])
		{
			is = TRUE;
			break ;
		}
		++i;
	}
	free(sorted);
	return (is);
}

int	valid(size_t argc, char **argv)
{
	char	*digit;
	size_t	i;
	ssize_t	value;

	i = 0;
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
		value = ft_atoss(argv[i]);
		if ((value > INT_MAX) || (value < INT_MIN))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

int	*parse(size_t argc, char **argv)
{
	int		*data;
	size_t	i;
	
	i = 0;
	data = NULL;
	if (!alloca_to((void **)&data, argc * sizeof(int)))
		return (NULL);
	while (i < argc)
	{
		data[i] = ft_atoi(argv[i]);
		++i;
	}
	return (data);
}

/* @brief Main function to parse income arguments.
 *
 * Takes size and arguments, parses
 * and validates duplicates and non-digits.
 *
 * @param argc Size of arguments array (without 0).
 * @params argv Arguments array (without program name).
 * 
 * @returns values Data parsed into array of integers.
 */
int	*prepare(int argc, char **argv)
{
	int *values;

	values = NULL;
	if (!valid(argc, argv))
		pexit(NULL, EXIT_FAILURE);
	values = parse(argc, argv);
	if (!values)
		pexit(NULL, EXIT_FAILURE);
	if (duplicated(values, argc))
	{
		free(values);
		pexit(NULL, EXIT_FAILURE);
	}
	return (values);
}
