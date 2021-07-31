/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 01:05:52 by rmander           #+#    #+#             */
/*   Updated: 2021/07/31 01:24:00 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include<sys/types.h> 

# define TRUE	1
# define FALSE	0

short int	alloca_to(void **ptr, ssize_t size);
void		*ft_memset(void *b, ssize_t c, size_t len);

#endif
