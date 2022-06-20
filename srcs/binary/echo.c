/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:50:17 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/20 13:09:36 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**ft_custom_countcharstr(const char *str)
{
	char	**av;
	size_t	len;
	size_t	i;
	char	c;

	i = 5;
	len = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace((char)(str)[i]))
			i++;
		if (str[i] && ('\'' == str[i] || '"' == str[i]))
		{
			c = (char)(str)[i++];
			i += 1 + ft_strnlen((char *)(str + i), c);
		}
		while (str[i] && !ft_isspace((char)(str)[i]))
			i++;
		len++;
	}
	printf("== FINALE===========+++=== len:%ld i:%ld str:%s+\n", len, i, str + i);
	av = (char **)ft_calloc(len + 1 + 1, sizeof(char *));
	wait(NULL);
	return (av);
}

static char	**ft_cast_av_echo(const char *str)
{
	char	**av;
	int		i;
	int		j;
	char	q;
	int		k;

	j = 1;
	if (!ft_iscinstr(str, '"') && !ft_iscinstr(str, '\''))
	{
		av = ft_split(str, ' ');
		return (av);
	}
	av = ft_custom_countcharstr(str);
	av[0] = ft_strndup((char *)(str), 4);
	i = 5;
	while (str[i])
	{
		if ('\'' == str[i] || '"' == str[i])
			q = str[i++];
		else
			q = ' ';
		k = ft_strnlen(str + i, q);
		printf("str\n");
		av[j++] = ft_strndup((char *)(str + i), k);
		i += k + 1 + ft_isspace(str[i + 1]);
	}
	return (av);
}

int	ft_exec_echo(t_src *src, int k)
{
	int		i;
	int		n_flag;
	char	**av;
	char	*tmp;

	ft_putendl_fd("EXO=========BUILD", 2);
	(void)(k);
	tmp = src->cmds[k];
	src->cmds[k] = ft_strtrim(src->cmds[k], " ");
	free(tmp);
	av = ft_cast_av_echo("echo hello         world    \"+      probeli  +\"slovechko");//src->cmds[k]);
	if (!av)
		return (0);
	n_flag = 0;
	if (av[1] && !ft_strncmp(av[1], "-n", 3))
		n_flag = 1;
	i = 1 + n_flag;
	while (i < src->argc)
	{
		ft_putstr_fd(av[i], 1);
		if ((i + 1) < src->argc)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	ft_splfree(av);
	return (1);
}
