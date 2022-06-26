/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:22:52 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/26 17:55:18 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_child_hd(t_pipex *s, char **line, char *stop, int *pipe_fd)
{
	close(pipe_fd[0]);
	while (ft_gnl_sh(&(*line), 10000, 0))
	{
		if (0 == ft_strncmp((*line), stop, ft_strlen(stop)))
		{
			ft_freesher(&s);
			free(*line);
			exit(0);
		}
		write(pipe_fd[1], (*line), ft_strlen((*line)));
		free(*line);
	}
}

void	ft_heredoc(t_pipex **s, char *stop)
{
	pid_t	pid;
	int		pipe_fd[2];
	char	*line;

	if (-1 == pipe(pipe_fd))
		ft_errorer(s, "Pipe error [hd]");
	else
	{
		pid = fork();
		if (pid == 0)
			ft_child_hd((*s), &line, stop, pipe_fd);
		else
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], 0);
			waitpid(pid, NULL, 0);
		}
	}
}
