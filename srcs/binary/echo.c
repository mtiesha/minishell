/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:50:17 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/20 18:15:04 by mtiesha          ###   ########.fr       */
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
	av = (char **)ft_calloc(len + 1 + 1, sizeof(char *));
	return (av);
}

static void	ft_new_array_cast(const char *str, char ***av, int i, int j)
{
	char	q;
	int		k;

	while (str[i])
	{
		k = 0;
		while (str[i] && ft_isspace((char)(str)[i]))
			i++;
		if (str[i] && ('\'' == str[i] || '"' == str[i]))
		{
			q = (char)(str)[i++];
			k += ft_strnlen((char *)(str + i), q);
		}
		while (str[i + k] && !ft_isspace((char)(str)[i + k]))
			k++;
		(*av)[j++] = ft_strndup((char *)(str + i), k);
		if (ft_strchr((*av)[j - 1], '"'))
			(*av)[j - 1] = ft_chardel(&(*av)[j - 1], \
				ft_strnlen((const char *)(*av)[j - 1], '"'));
		i += k;
	}
}

static char	**ft_cast_av_echo(const char *str, char **tmp)
{
	char	**av;
	int		i;
	int		j;

	j = 1;
	if (!ft_iscinstr(str, '"') && !ft_iscinstr(str, '\''))
	{
		av = ft_split(str, ' ');
		return (av);
	}
	(*tmp) = ft_strtrim(str, " ");
	av = ft_custom_countcharstr((const char *)(*tmp));
	av[0] = ft_strndup((*tmp), 4);
	i = 5;
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
