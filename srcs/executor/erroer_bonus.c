/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erroer_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:10:31 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/16 19:06:22 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_freesher(t_pipex **s)
{
	if (*s)
	{
		if ((*s)->fd0 != 0)
			close((*s)->fd0);
		if ((*s)->fd1 != 1)
			close((*s)->fd1);
		if ((*s)->path)
			ft_splfree((*s)->path);
		if ((*s)->cmd)
			ft_splarrfree((*s)->cmd);
		free(*s);
		*s = NULL;
	}
}

void	ft_errorer(t_pipex **s, char *code)
{
	if (NULL == code)
		perror("Error:");
	else
		ft_putendl_fd(code, 2);
	ft_freesher(&(*s));
	//exit(1);
}
