/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:58:46 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/23 06:23:58 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_lexer(t_src *s)
{
	int		i;
	char	q;
	int		*lex_arr;

	i = 0;
	while (s->str[i])
	{
		if (';' == s->str[i])
			return (1 && ft_putendl_fd("lexer error [semcl]", 2));
		if ('"' == s->str[i] || '\'' == s->str[i])
		{
			q = s->str[i++];
			while (q != s->str[i] && s->str[i])
				i++;
			if (!s->str[i])
				return (1 && ft_putendl_fd("lexer error [unclose quotes]", 2));
		}
		i++;
	}
	return (0);
}
