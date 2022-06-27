/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:50:17 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/27 10:52:40 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**ft_custom_countcharstr(const char *str)
{
	char	**av;
	size_t	len;
	size_t	i;
	int		quot;
	char	c;

	i = 5;
	len = 0;
	quot = 0;
	while (i <= ft_strlen(str) && str[i])
	{
		if ('\'' == str[i] || '"' == str[i])
			c = str[i];
		if (c == str[i] && 0 == quot && ft_iscinstr(str + i + 1, c))
			quot = 1;
		else if (c == str[i] && 1 == quot)
			quot = 0;
		if (i <= ft_strlen(str) && ' ' == str[i] && !quot)
			len++;
		i++;
	}
	len++;
	printf("LEN CUSTOM CCH:%ld\n", len);
	av = (char **)ft_calloc(len + 1 + 1, sizeof(char *));
	return (av);
}

static void	ft_new_array_cast(const char *str, char ***av, int i, int j)
{
	char	c;

	c = ' ';
	while (i <= (int)(ft_strlen(str)))
	{
		if (c == ' ' && ('\'' == str[i] || '"' == str[i]))
			c = str[i++];
		if (c != ' ' && ('\'' == str[i] || '"' == str[i]))
		{
			c = ' ';
			i++;
		}
		(*av)[j++] = ft_strndup((char *)str + i, \
			ft_strnlen((char *)str + i, c));
		i += 1 + ft_strnlen((char *)str + i, c);
	}
}

static char	**ft_cast_av_echo(const char *str, char **tmp)
{
	char	**av;
	int		i;
	int		j;

	j = 1;
	i = 5;
	if (!ft_iscinstr(str, '"') && !ft_iscinstr(str, '\''))
	{
		av = ft_split(str, ' ');
		return (av);
	}
	(*tmp) = ft_strtrim(str, " ");
	av = ft_custom_countcharstr((const char *)(*tmp));
	av[0] = ft_strndup((*tmp), 4);
	ft_new_array_cast((const char *)(*tmp), &av, i, j);
	free(*tmp);
	return (av);
}

int	ft_exec_echo(t_src *src, int k)
{
	int		i;
	int		n_flag;
	char	**av;
	char	*tmp;
	int		avlen;

	av = ft_cast_av_echo(src->cmds[k], &tmp);
	if (!av)
		return (1);
	avlen = ft_spllen(av);
	n_flag = 0;
	if (av[1] && !ft_strncmp(av[1], "-n", 3))
		n_flag = 1;
	i = n_flag + 1;
	while (i < avlen)
	{
		ft_putstr_fd(av[i], 1);
		if ((i + 1) < avlen)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	ft_splfree(av);
	return (0);
}
