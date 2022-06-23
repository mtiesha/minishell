/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:58:46 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/23 20:36:18 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_syntax_check(char *str)
{
	int		i;
	char	q;

	i = 0;
	while (str[i])
	{
		if (';' == str[i])
			return (1 && ft_putendl_fd("lexer error [semcl]", 2));
		if ('\\' == str[i])
			return (1 && ft_putendl_fd("lexer error [backslash]", 2));
		if ('"' == str[i] || '\'' == str[i])
		{
			if (str[i + 1])
			{
				q = str[i++];
				while (q != str[i] && str[i])
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

int	ft_lexer(t_src *s)
{
	printf("---------------LEXER---------------\n");
	if (ft_syntax_check(s->str))
		return (1);
	s->str = ft_dollar_opener(s);
	if (!s->str)
		return (1);
	if (ft_iscinstr(s->str, '>') || ft_iscinstr(s->str, '<'))
	{
		s->str = ft_redirecter(s);
		if (!s->str)
		{
			ft_putendl_fd("lexer error [<> redirect]", 2);
			return (1);
		}
	}
	printf("---------------LEXER---------------\n");
	return (0);
}
