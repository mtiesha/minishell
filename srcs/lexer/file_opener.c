/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 06:31:15 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/28 17:57:32 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_set_mask(char const *str)
{
	int	mask;

	mask = 0;
	if ('<' == *str && *(str + 1) && ' ' == *(str + 1))
		mask = 0;
	else if ('>' == *str && *(str + 1) && ' ' == *(str + 1))
		mask = 1;
	else if ('>' == *str && *(str + 1) && '>' == *(str + 1))
		mask = 2;
	return (mask);
}

static int	ft_gate_try_open(t_src *s, char *ptr, int mask, int free_str_flag)
{
	int	fd;

	fd = ft_try_open_file(ptr, mask);
	if (-1 == fd)
	{
		ft_putstr_fd("open file error [<> F]: ", 2);
		ft_putendl_fd(ptr, 2);
		free(ptr);
		s->ret = 126;
		if (free_str_flag)
			free(s->str);
	}
	return (fd);
}

static void	ft_free_part(int *i, int k, char)
{
	(*i) += k - (*i);
	k = 0;
	while (s->str[(*i)] && ' ' != s->str[(*i)])
		s->str = ft_chardel(&s->str, (*i));
	val = ft_itoa(fd);
	while (val[k])
		s->str = ft_charadd(&s->str, (*i)++, val[k++]);
	(*i) -= k;
	free(val);
}

int	ft_open_onmask(t_src *s, int *i, int free_str_flag)
{
	int		k;
	int		mask;
	char	*ptr;
	char	*val;
	int		fd;

	k = (*i);
	mask = ft_set_mask((char const *)(s->str + k));
	while (' ' != s->str[k])
		k++;
	k++;
	ptr = ft_strndup(s->str + k, ft_strnlen(s->str + k, ' '));
	fd = ft_gate_try_open(s, ptr, mask, free_str_flag);
	if (-1 == fd)
		return (fd);
	if (free_str_flag)
		ft_free_part(ne hvataet argumenta chtob vvesti);
	free(ptr);
	return (fd);
}

char	*ft_file_opener(t_src *s)
{
	int		i;
	int		fd;
	int		c_pipes;

	fd = -2;
	c_pipes = ft_count_char(s->str, '|');
	i = 1 + ft_strnlen(s->str, ' ');
	while (i <= (int)(ft_strlen(s->str)) && s->str[i])
	{
		if (s->str[i] && ('<' == s->str[i] || '>' == s->str[i]))
		{
			if ('>' == s->str[i] && !c_pipes)
				i++;
			else
			{
				fd = ft_open_onmask(s, &i, 1);
				if (-1 == fd)
					return (NULL);
			}
		}
		if ('|' == s->str[i])
			c_pipes--;
		i++;
	}
	return (s->str);
}
