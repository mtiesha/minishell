/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erroer_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:10:31 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/26 17:54:23 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_freesher(t_pipex **s)
{
	int	k;

	k = 0;
	if (*s)
	{
		if ((*s)->red)
		{
			while (k <= ((*s)->gnr * 2) - 1)
			{
				if (-1 != (*s)->red[k++])
					close((*s)->red[k - 1]);
			}
			free((*s)->red);
		}
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

int	ft_errorer(t_pipex **s, char *code)
{
	int	ret;

	ret = (*s)->ret_code;
	if (NULL == code)
		perror("Error:");
	else
		ft_putendl_fd(code, 2);
	ft_freesher(&(*s));
	return (ret);
}
