/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 06:31:15 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/24 08:23:44 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_set_mask(char const *str)
{
	int	mask;

	mask = 0;
	if ('<' == *str && *str + 1 && ' ' == *str + 1)
		mask = 0;
	else if ('>' == *str && *str + 1 && ' ' == *str + 1)
		mask = 1;
	else if ('>' == *str && *str + 1 && '>' == *str + 1)
		mask = 2;
	return (mask);
}

char	*ft_file_opener(t_src *s)
{
	size_t	i;
	int		len_file;
	int		fd;
	int		mask;
	char	*ptr;
	char	*val;

	i = 0;
	len_file = 0;
	fd = -2;
	while (i <= ft_strlen(s->str) && s->str[i])
	{
		printf("FILE OPENER");
		if (s->str[i] && ('<' == s->str[i] || '>' == s->str[i]))
		{
			if ('<' == s->str[i + 1])
			{
				i += 1 + ft_strnlen(s->str + i, ' ');
				continue ;
			}
			mask = ft_set_mask((char const *)(s->str + i));
			while (' ' != s->str[i])
				i++;
			i++;
			len_file += 1 + ft_strnlen(s->str + i, ' ');
			ptr = ft_strndup(s->str + i, ft_strnlen(s->str + i, ' '));
			fd = ft_try_open_file(ptr, mask);
			if (-1 == fd)
			{
				ft_putstr_fd("open file error [<> F]: ", 2);
				ft_putendl_fd(ptr, 2);
				ft_multifree(ptr, s->str, NULL);
				return (NULL);
			}
			while (' ' != s->str[i])
				s->str = ft_chardel(&s->str, i);
			val = ft_itoa(fd);
			while (*val)
				s->str = ft_charadd(&s->str, i, *val++);
			// free(ptr);
			ft_multifree(ptr, val, NULL);
		}
		i++;
	}
	return (s->str);
}
