/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 06:31:15 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/26 13:54:37 by mtiesha          ###   ########.fr       */
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

	printf("Tak EBAT: %s\n", ptr);
	fd = ft_try_open_file(ptr, mask);
	if (-1 == fd)
	{
		ft_putstr_fd("open file error [<> F]: ", 2);
		ft_putendl_fd(ptr, 2);
		free(ptr);
		if (free_str_flag)
			free(s->str);
	}
	return (fd);
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
	printf("2222222:%s\n", s->str + k);
	ptr = ft_strndup(s->str + k, ft_strnlen(s->str + k, ' '));
	fd = ft_gate_try_open(s, ptr, mask, free_str_flag);
	if (-1 == fd)
		return (fd);
	if (free_str_flag)
	{
		(*i) += k - (*i);
		printf("3333333:%s\n", s->str);
		k = 0;
		while (s->str[(*i)] && ' ' != s->str[(*i)])
			s->str = ft_chardel(&s->str, (*i));
		val = ft_itoa(fd);
		while (val[k])
			s->str = ft_charadd(&s->str, (*i)++, val[k++]);
		(*i) -= k;
		free(val);
	}
	free(ptr);
	return (fd);
}

char	*ft_file_opener(t_src *s)
{
	int		i;
	int		fd;
	int		c_pipes;

	fd = -2;
	printf("++++++++++++FILEOPENER+++++++++\n");
	c_pipes = ft_count_char(s->str, '|');
	printf("c_pipes START : %d\n", c_pipes);
	i = 1 + ft_strnlen(s->str, ' ');
	while (i <= (int)(ft_strlen(s->str)) && s->str[i])
	{
		printf("s->str + i:ST+%s+\n", s->str + i);
		if (s->str[i] && ('<' == s->str[i] || '>' == s->str[i]))
		{
			printf("c_pipes:%d\n", c_pipes);
			if ('>' == s->str[i] && !c_pipes)
			{
				printf("I SUKA ++\n");
				i++;
			}
			else
			{
				printf("do open_mask:%s\n", s->str + i);
				fd = ft_open_onmask(s, &i, 1);
				if (-1 == fd)
					return (NULL);
				printf("posle open_mask:%s\n", s->str + i);
			}
		}
		printf("i:%d  strlen:%d\n", i, (int)(ft_strlen(s->str)));
		printf("s->str + i:END+%s+\n", s->str + i);
		if ('|' == s->str[i])
			c_pipes--;
		i++;
	}
	printf("++++++++++++FILEOPENER+++++++++\n");
	return (s->str);
}
