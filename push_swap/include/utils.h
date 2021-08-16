/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmander <rmander@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 01:05:52 by rmander           #+#    #+#             */
/*   Updated: 2021/08/16 05:06:36 by rmander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/types.h>

# define TRUE	1
# define FALSE	0

# define IN		1
# define OUT	0

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

short int	alloca_to(void **ptr, size_t size);
void		*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_atoi(const char *str);
ssize_t		ft_atoss(const char *str);
int			ft_isspace(int c);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
size_t		ft_strlen_until(const char *s, const char sym);
char		*ft_strdup_until(const char *s1, const char sym);
char		*ft_strchr(const char *s, int c);
char		**ft_splitf(char const *s, int (*f)(int));
size_t		ft_strslen(char **strs);
int			*ft_qsort(int *values, size_t l, size_t r);
short int	issorted(int *values, size_t size, short int asc);
void		swap(int *l, int *r);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
int			ft_strcmp(const char *s1, const char *s2);

#endif
