/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:08:33 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/02 17:06:44 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	skip_spaces(char **str)
{
	while ((*str) && ft_isspace(*(*str)))
		(*str)++;
}

char		**copy_args(t_src *src)
{
	int		i;
	char	**args;

	i = 0;
	while (src->argv[i] && ft_memcmp(src->argv[i], "<", 2))
		i++;
	args = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (src->argv[i] && ft_memcmp(src->argv[i], "<", 2))
	{
		args[i] = ft_strdup(src->argv[i]);
		i++;
	}
	return (args);
}

static int	ft_strlen_arg(char *str)
{
	int i;//it count argv in str

	i = 0;
	if (str[i] == '<' || str[i] == '>' || str[i] == '|')//  str[i] == '=' ||
	{
		if (str[i] == '>' && str[i + 1] == '>')
			i++;
		i++;
	}
	else
	{
		while (str[i] && !ft_isspace(str[i]) && str[i] != '<' \
			&& str[i] != '>' && str[i] != '|')// && str[i] != '='
		{
			if (str[i] == '\'' || str[i] == '"')
			{
				i++;
				i += ft_strlen_arg_token(str + i, str[i - 1]);
				if (!(str[i]))
					return (i);
			}
			i++;
		}
		//if (str[i] == '=')
		//	i++;
	}
	return (i);
}

int	count_args(char *str)
{
	int		n;

	n = 0;
	skip_spaces(&str);
	while (*str)
	{
		skip_spaces(&str);
		n++;
		str += ft_strlen_arg(str);
		skip_spaces(&str);
	}
	return (n);
}

void	set_args(char **argv, char *str, int argc)
{//convert str(from readline) to -> argc and argv
	int		i;
	int		len;

	i = 0;
	skip_spaces(&str);
	while (i < argc)
	{
		skip_spaces(&str);
		len = ft_strlen_arg(str);
		argv[i] = ft_strndup(str, len);
		rm_token(&(argv[i]));
		i++;
		str += len;
		skip_spaces(&str);
	}
}
