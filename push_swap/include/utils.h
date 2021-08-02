/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 01:05:52 by rmander           #+#    #+#             */
/*   Updated: 2021/08/02 23:43:35 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include<sys/types.h>

# define TRUE	1
# define FALSE	0

short int	alloca_to(void **ptr, size_t size);
void		*ft_memset(void *b, int c, size_t len);
int			ft_atoi(const char *str);
int			ft_isspace(int c);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
size_t		ft_strlen_until(const char *s, const char sym);
char		*ft_strdup_until(const char *s1, const char sym);
char		*ft_strchr(const char *s, int c);

#endif
