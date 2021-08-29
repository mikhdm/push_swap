/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 08:57:45 by rmander           #+#    #+#             */
/*   Updated: 2021/08/29 09:01:33 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include <stddef.h>

int	duplicated(int *values, size_t size);
int	valid(size_t argc, char **argv);
int	*parse(size_t argc, char **argv);
int	*prepare(int argc, char **argv);

# endif
