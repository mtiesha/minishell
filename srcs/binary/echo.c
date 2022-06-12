/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 12:50:17 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/06 14:35:12 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exec_echo(t_src *src, int fd)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	if (!ft_memcmp(src->argv[1], "-n", 3))
		n_flag = 1;
	i = 1 + n_flag;// start from 0=[echo] 1=[-n] 2=[hello] <- there 3=[its me] || 0=[echo] 1=[hello] <- there 2=[its me]
	while (i < src->argc)
	{
		ft_putstr_fd(src->argv[i], fd);
		if ((i + 1) < src->argc)// +1 don't print " ", if its last arg
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", fd);
}
