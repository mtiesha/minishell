/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:09:49 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/15 12:15:46 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_add_mshlvl(char **envp)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = (char **)ft_calloc(2 + ft_spllen(envp), sizeof(char *));
	while (envp[i])
	{
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	tmp[i] = ft_strdup("MSHLVL=0");
	return (tmp);
}

void	ft_sig_handler_b(int sig)
{
	(void)(sig);
}
