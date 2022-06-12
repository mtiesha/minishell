/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erroer_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:10:31 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/03 15:10:03 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_freesher(t_pipex **s)
{
	if (*s)
	{
		if ((*s)->path)
			ft_splfree((*s)->path);
		if ((*s)->cmd)
			ft_splarrfree((*s)->cmd);
		free(*s);
		*s = NULL;
	}
}

void	ft_errorer(t_pipex **s)
{
	perror("Error");
	ft_freesher(&(*s));
	exit(1);
}
