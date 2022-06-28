/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:02:39 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/28 17:28:46 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_open_last_file(t_pipex **s, char **argv, int j)
{
	if (0 == ft_strncmp(">", argv[j], 2))
	{
		(*s)->fd1 = open(argv[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if ((*s)->fd1 == -1)
			ft_errorer(s, NULL);
	}
	else if (0 == ft_strncmp(">>", argv[j], 3))
	{
		(*s)->fd1 = open(argv[j + 1], O_WRONLY | O_APPEND | O_CREAT, 0777);
		if ((*s)->fd1 == -1)
			ft_errorer(s, NULL);
	}
}

void	ft_open_first_file(t_pipex **s, char **argv)
{
	if (ft_isfile((*argv)))
	{
		(*s)->fd0 = open(*(argv), O_RDONLY, 0777);
		if (-1 == (*s)->fd0)
			ft_errorer(s, NULL);
	}
}
