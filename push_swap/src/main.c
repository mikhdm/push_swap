/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 23:08:41 by rmander           #+#    #+#             */
/*   Updated: 2021/08/02 23:43:44 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"
#include "error.h"
#include "utils.h"
#include <stddef.h>
#include <limits.h>
#include <stdlib.h>

int	max(t_stack *stack)
{
	int i;
	int imax;
	int *data;

	i = 0;
	imax = i;
	while (++i < stack->size)
		if (data[i] > data[imax])
			imax = i;
}

int	valid(size_t argc, char **argv)
{
	char	*digit;
	size_t	i;

	i = 0;
	digit = NULL;
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

int getarg(char **envp)
{
	char	*curr;

	curr = NULL;
	while (*envp)
	{
		curr = *envp;
		curr = ft_strdup_until(*envp, '=');
		if (ft_strcmp(curr, "ARG"))
		{
			free(curr);
			curr = ft_strchr(*envp, '=');
			ft_strdup_until(++curr, '\0');
			return 
		}
	}
}

int main(int argc, char **argv, char **envp)
{
	t_data	data;

	data = (t_data){.a = NULL, .b = NULL, .ops = NULL};
	if (argc == 1)
		pexit(NULL, EXIT_FAILURE);
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
