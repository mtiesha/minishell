/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:02:39 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/21 18:03:18 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_open_last_file(t_pipex **s, char **argv)
{
	if (0 == ft_strncmp(">", *(argv), 2))
	{
		printf("~fileend:%s\n", *(1 + argv));
		(*s)->fd1 = open(*(++argv), O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if ((*s)->fd1 == -1)
			ft_errorer(s, NULL);
	}
	else if (0 == ft_strncmp(">>", *(argv), 3))
	{
		(*s)->fd1 = open(*(++argv), O_WRONLY | O_APPEND | O_CREAT, 0777);
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
