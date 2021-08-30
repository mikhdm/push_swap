/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 06:09:59 by rmander           #+#    #+#             */
/*   Updated: 2021/08/30 08:24:02 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "parse.h"
#include "op.h"
#include "push_swap.h"
#include "reader.h"
#include "get_next_line.h"
#include "optimize.h" 
#include <unistd.h>
#include <stdlib.h>

void	ops_exec(t_data *data, t_list *ops)
{
	while (ops)
	{
		op(data, (char *)ops->content);
		ops = ops->next;
	}
}

static	void	populate(t_data *data, int *values, size_t size)
{
	data->values = values;
	data->a = build(indexify(data, size), size);
	if (!data->a)
		pexit(data, EXIT_FAILURE);
	data->b = build(NULL, size);
	if (!data->b)
		pexit(data, EXIT_FAILURE);
	if (empty(data->a))
		pexit(data, EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_list	*ops;
	int		*values;
	char	*verdict;

	if ((argc - 1) == 0)
		return (0);
	values = prepare(--argc, ++argv);
	data = (t_data){.a = NULL, .b = NULL, .ops = NULL, .chunks = NULL,
		.values = NULL};
	populate(&data, values, argc);
	ops = ops_read(&data);
	ops_exec(&data, ops);
	if (issorted(data.a->data, data.a->size, DESC) && empty(data.b))
		verdict = "OK\n";
	else
		verdict = "KO\n";
	write(STDOUT_FILENO, verdict, ft_strlen_until(verdict, '\0'));
	ft_lstclear(&ops, free);
	cleanup(&data);
	return (0);
}
