/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:13:02 by marvin            #+#    #+#             */
/*   Updated: 2022/05/11 19:02:56 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void		rm_char(char **str, int j)
{
	char *bef;
	char *aux;

	bef = ft_strldup(*str, j);
	aux = ft_strdup(*str + j + 1);
	free(*str);
	*str = ft_strjoin(bef, aux);
	free(aux);
	free(bef);
}

static void	rm_backslash(char **arg, int *i)
{
	while ((*arg)[*i])
	{
		if ((*arg)[*i] == '\\' && is_token((*arg)[*i + 1]))
			rm_char(arg, *i);
		else if ((*arg)[*i] == '"')
			break ;
		(*i)++;
	}
}

void		rm_token(char **arg)
{
	int		i;

	i = 0;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '\'')
		{
			rm_char(arg, i);
			i += ft_strlen_char(*arg + i, '\'');
			rm_char(arg, i);
		}
		else if ((*arg)[i] == '"')
		{
			rm_char(arg, i);
			rm_backslash(arg, &i);
			rm_char(arg, i);
		}
		else if (((*arg)[i] == '\\') &&
		(is_token((*arg)[i + 1]) || (*arg)[i + 1] == '\''))
			rm_char(arg, i++);
		else
			i++;
	}
}
