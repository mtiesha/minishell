/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:52:08 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/24 18:03:46 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_only_one_red(t_src *s)
{
	int		i;
	char	c;

	i = 0;
	while (s->str[i])
	{
		if (i > 0 && s->str[i - 1] != ' ' && \
			('"' == s->str[i] || '\'' == s->str[i]))
		{
			c = s->str[i];
			s->str[i] = s->str[i - 1];
			s->str[i - 1] = c;
			i = 0;
		}
		i++;
	}
	return (s->str);
}
