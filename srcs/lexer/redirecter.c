/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:26:22 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/24 14:22:59 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_redirecter_logic(t_src *s, char direct)
{
	int		i;

	i = 0;
	while (s->str[i])
	{
		printf("REDIR LOGIC");
		if (direct == s->str[i])
		{
			// if (i > 0 && ' ' != s->str[i - 1])
			// {
			// 	if (' ' != s->str[i - 1])
				s->str = ft_charadd(&s->str, i++, ' ');
				if (direct == s->str[++i])
					i++;
			// }
			// if (i < ft_strlen(s->str) && ' ' != s->str[i + 1])
			// {
			// 	if (' ' != s->str[i])
				s->str = ft_charadd(&s->str, i++, ' ');
			// }
		}
		i++;
	}
}

char	*ft_redirecter(t_src *s)
{
	int		err;
	char	*ptr;

	err = 0;
	ptr = ft_strnstr(s->str, "><", ft_strlen(s->str));
	if (!ptr)
		ptr = ft_strnstr(s->str, "<>", ft_strlen(s->str));
	if (ptr)
		err = 1;
	else
	{
		if (ft_iscinstr(s->str, '<'))
			ft_redirecter_logic(s, '<');
		if (ft_iscinstr(s->str, '>'))
			ft_redirecter_logic(s, '>');
	}
	if (err)
	{
		free(s->str);
		s->ret = 127;
		return (NULL);
	}
	return (s->str);
}
