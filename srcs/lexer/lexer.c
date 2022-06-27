/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:58:46 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/27 10:36:03 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_syntax_help(char c)
{
	if (';' == c)
		return (1 && ft_putendl_fd("lexer error [semcl]", 2));
	if ('\\' == c)
		return (1 && ft_putendl_fd("lexer error [backslash]", 2));
	return (0);
}

static int	ft_syntax_check(char *str)
{
	int		i;
	char	q;

	i = 0;
	while (str[i])
	{
		if (ft_syntax_help(str[i]))
			return (1);
		if ('"' == str[i] || '\'' == str[i])
		{
			if (str[i + 1])
			{
				q = str[i++];
				while (str[i] && q != str[i])
					i++;
				if (!str[i])
					return (1 && ft_putendl_fd("lexer error [quotes]", 2));
			}
			else
				return (1 && ft_putendl_fd("lexer error [quotes]", 2));
		}
		i++;
	}
	return (0);
}

static int	ft_gate_lexer(t_src *s)
{
	char	*tmp;

	s->str = ft_dollar_opener(s);
	if (!s->str)
		return (127);
	printf("9999999999999999999999999999\nSTR+%s\n99999999999999999999\n", s->str);
	s->str = ft_redirecter(s);
	if (!s->str)
	{
		ft_putendl_fd("lexer error [<> redirect]", 2);
		return (127);
	}
	ft_only_one_red(s);
	ft_putendl_fd("here", 2);
	ft_putendl_fd(s->str, 2);
	// printf("COMMAND- med lexer: %s\n", s->str);//< f2 < f4 ls -la > f45 | wc -l >> f22
	tmp = s->str;
	s->str = ft_strtrim(s->str, " ");
	free(tmp);
	s->str = ft_file_opener(s);
	if (!s->str)
		return (127);
	if (ft_iscinstr(s->str, '|'))
	{
		ft_path_ejecter(s);
		if (!s->str)
			return (1);
	}
	return (0);
}

int	ft_lexer(t_src *s)
{
	printf("---------------LEXER---------------\n");
	if (ft_syntax_check(s->str))
		return (1);
	if (ft_gate_lexer(s))
		return (1);
	printf("COMMAND-%s\n", s->str);
	printf("---------------LEXER---------------\n");
	return (0);
}
