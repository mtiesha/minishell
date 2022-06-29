/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:52:08 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/28 21:17:28 by mtiesha          ###   ########.fr       */
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

static int	ft_del_ptr(t_src *s, int *i, int *ptr, int *end)
{
	int	cut;
	int	fd;

	if (-1 == (*ptr))
		(*ptr) = (*i);
	else if (-1 != (*ptr) && s->str[(*ptr)] == s->str[(*i)])
	{
		cut = 1 + ft_strnlen(s->str + (*ptr), ' ');
		cut += 1 + ft_strnlen(s->str + (*ptr) + cut, ' ');
		if ((*i) - cut)
			(*i) -= cut + 1;
		(*end) -= cut;
		fd = ft_open_onmask(s, ptr, 0);
		if (-1 == fd)
			return (126);
		while (cut)
		{
			s->str = ft_chardel(&s->str, (*ptr));
			cut--;
		}
		(*ptr) = -1;
	}
	return (0);
}

static int	ft_only_one_red_r(t_src *s, int i, int end)
{
	int		ptr_l;
	int		ptr_r;

	ptr_l = -1;
	ptr_r = -1;
	end = end + ft_strnlen(s->str + i, '|') + 1;
	while (i <= end)
	{
		if (0 == s->ret && i < (int)(ft_strlen(s->str)) && '<' == s->str[i])
			s->ret = ft_del_ptr(s, &i, &ptr_l, &end);
		if (0 == s->ret && i < (int)(ft_strlen(s->str)) && '>' == s->str[i])
			s->ret = ft_del_ptr(s, &i, &ptr_r, &end);
		i++;
		if (0 == s->ret && i > 1 && i < (int)(ft_strlen(s->str))
			&& ('<' == s->str[i - 1] || '>' == s->str[i - 1]))
			i++;
	}
	if (0 == s->ret && i < (int)(ft_strlen(s->str)))
		s->ret = ft_only_one_red_r(s, i, end);
	return (s->ret);
}

int	ft_only_one_red(t_src *s)
{
	s->ret = 0;
	if (ft_strncmp(s->str, "echo ", 5))
		s->str = ft_deldoublec(&s->str, ' ');
	s->ret = ft_only_one_red_r(s, 0, 0);
	if (s->ret)
	{
		free(s->str);
		return (s->ret);
	}
	s->str = ft_cleaner(&s->str);
	return (s->ret);
}
