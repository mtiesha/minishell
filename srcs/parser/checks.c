/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 08:18:36 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/07 12:58:12 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_wrong_pipe(t_src *s)
{
	char	*str;

	str = s->str;
	while (*str)
	{
		if (*str == '|')
		{
			ft_putstr_fd(MES_ERR_SYNT_P, 2);
			s->ret = 258;
			return (0);
		}
		if (*str == ' ' || *str == '\t')
			str++;
		else
			return (1);
	}
	s->ret = 0;
	return (0);
}
