/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:52:08 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/24 20:01:24 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_path_ejecter(t_src *s)
{
	int	i;
	int	k;

	i = 0;
	while (s->str[i])
	{
		if ('/' == s->str[i] || 0 == ft_strncmp(s->str + i, "./", 2) \
			|| 0 == ft_strncmp(s->str + i, "../", 3))
		{
			k = 0;
			while (s->str[i + k] && !ft_isspace(s->str[i + k]))
				k++;
			while ('/' != s->str[i + k])
				k--;
			k++;
			while (k)
			{
				s->str = ft_chardel(&s->str, i);
				k--;
			}
			i = 0;
		}
		i++;
	}
}

// void	ft_del_absolute_path(t_src *s)
// {
// 	char	*ptr;

// 	ptr = ft_strnstr(s->str, "../", ft_strlen(s->str));
// 	if (!ptr)
// 		ptr = ft_strnstr(s->str, "./", ft_strlen(s->str));
// 	if (!ptr)
// 		ptr = ft_strnstr(s->str, "/", ft_strlen(s->str));
// 	while (ptr)
// 	{
// 		if (ptr)
// 		{
// 			ft_del_path(&ptr);
// 			free(s->str);
// 			s->str = ptr;
// 			free(ptr);
// 		}
// 		ptr = ft_strnstr(s->str, "../", ft_strlen(s->str));
// 		if (!ptr)
// 			ptr = ft_strnstr(s->str, "./", ft_strlen(s->str));
// 		if (!ptr)
// 			ptr = ft_strnstr(s->str, "/", ft_strlen(s->str));
// 	}
// }

// static char	*ft_only_one_red_r(t_src *s)
// {
// 	int		i;
// 	int		end;
// 	char	*red_t;
// 	char	*ptr;

// 	i = 0;// this function delete all < f2 < f3 < f4 and ostavlyaet tolko last
// 	if (!ft_iscinstr(s->str, '|'))
// 		return (s->str);
// 	while (s->str[i])
// 	{
// 		end = ft_strnlen(s->str + i, '|');
// 		while (i <= end)
// 		{
// 			if ('<' == s->str[i] || '>' == s->str[i])
// 			{
// 				ptr = s->str + i;
// 				if (!red_t || red_t[0] == s->str[i])
// 				{
// 					ft_delold(&red_t);
// 					red_t = ptr;
// 					i++;
// 				}
// 			}
// 			i++;
// 		}
// 		i++;
// 	}
// }

char	*ft_only_one_red(t_src *s)
{
	int		i;
	char	c;

	i = 0;
	while (s->str[i])
	{
		if (i > 0 && s->str[i - 1] != ' ' && \
			('"' == s->str[i] || '\'' == s->str[i]))
		{
			c = s->str[i];
			s->str[i] = s->str[i - 1];
			s->str[i - 1] = c;
			i = 0;
		}
		i++;
	}
	// s->str = ft_only_one_red_r(s);
	return (s->str);
}
