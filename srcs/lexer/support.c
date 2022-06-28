/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:52:08 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/28 08:09:43 by mtiesha          ###   ########.fr       */
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
		printf("\n\nVIREZAEM\n");
		printf("cmd_part:%s+\n", s->str + (*i));
		cut = 1 + ft_strnlen(s->str + (*ptr), ' ');
		cut += 1 + ft_strnlen(s->str + (*ptr) + cut, ' ');
		printf("I:%d cut:%d\n", (*i), cut);
		if ((*i) - cut)
			(*i) -= cut + 1;
		(*end) -= cut;
		printf("\n\nDELPTR {} s->str{ptr}+%s+\nCCUut:%d\n", s->str + (*ptr), cut);
		printf("_ptr_%d\n", (*ptr));
		fd = ft_open_onmask(s, ptr, 0);
		if (-1 == fd)
			return (126);
		printf("_ptr_%d\n", (*ptr));
		printf("111111_OTKRITO:+%s+\n\n", s->str + (*ptr));
		while (cut)
		{
			s->str = ft_chardel(&s->str, (*ptr));
			printf("DEL+%s+\n %d\n", s->str + (*ptr), cut);
			cut--;
		}
		(*ptr) = -1;
		printf("VIREZAEM\n\n");
	}
	return (0);
}

static int	ft_only_one_red_r(t_src *s, int i, int end)
{
	int		ptr_l;
	int		ptr_r;

	ptr_l = -1;// ls -la > f2 | < f3 <f5 wc -l
	ptr_r = -1;
	// printf("str+i:%s\n", s->str + i);
	// printf("~~+~~i:%d\n", i);
	end = end + ft_strnlen(s->str + i, '|') + 1;
	printf("~~~~END:%d\n", end);
	while (i <= end)
	{
		if (i < (int)(ft_strlen(s->str)))
			printf("CUTTER=i%d=end%d=mem%d==:%s\n", i, end, ptr_l, s->str + i);
		if (i < (int)(ft_strlen(s->str)) && '<' == s->str[i])
		{
			s->ret = ft_del_ptr(s, &i, &ptr_l, &end);
			if (0 != s->ret)
				return (s->ret);
		}
		if (i < (int)(ft_strlen(s->str)) && '>' == s->str[i])
		//	&& '>' != s->str[i + 1])
		{
			s->ret = ft_del_ptr(s, &i, &ptr_r, &end);
			if (0 != s->ret)
				return (s->ret);
		}
		printf("i <= end ptr_l:%d str+%s+\n\n\n", ptr_l, s->str);
		i++;
		if (i > 1 && i < (int)(ft_strlen(s->str))
			&& ('<' == s->str[i - 1] || '>' == s->str[i - 1]))
			i++;
		// if (i > 35)
		// 	exit(0);
	}
	// printf("~~~~i:%d\n", i);
	// printf("str before recursy:+%s+\ni:%d end:%d\n", s->str, i, end);
	if (0 == s->ret && i < (int)(ft_strlen(s->str)))
	{
		// printf("INTORECURSY\n");
		s->ret = ft_only_one_red_r(s, i, end);
	}
	printf("str after recursy:%s\n", s->str);
	return (s->ret);
}

int	ft_only_one_red(t_src *s)
{
	// int		i;
	// char	c;

	s->ret = 0;
	// i = 0;
	// while (s->str[i])
	// {
	// 	if (i > 0 && s->str[i - 1] != ' ' &&
	// 		('"' == s->str[i] || '\'' == s->str[i]))
	// 	{
	// 		c = s->str[i];
	// 		s->str[i] = s->str[i - 1];
	// 		s->str[i - 1] = c;
	// 		i = 0;
	// 	}
	// 	i++;
	// 	printf("tuta\n");
	// }
	if (ft_iscinstr(s->str, '|'))
	{
		s->str = ft_deldoublec(&s->str, ' ');
		s->ret = ft_only_one_red_r(s, 0, 0);
		if (s->ret)
		{
			free(s->str);
			return (s->ret);
		}
		s->str = ft_cleaner(&s->str);//maybe delpipe
	}
	return (s->ret);
}
