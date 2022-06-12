/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:23:47 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/12 14:41:35 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_heredoc(t_pipex **s, char *stop)
{
	pid_t	pid;
	int		pipe_fd[2];
	char	*line;

	if (-1 == pipe(pipe_fd))
		ft_errorer(s);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		while (ft_gnl_sh(&line, 10000, 0))
		{
			if (0 == ft_strncmp(line, stop, ft_strlen(stop)))
				exit(0);
			write(pipe_fd[1], line, ft_strlen(line));
			//maybe need free(&line);
		}
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		waitpid(pid, NULL, 0);
	}
}

static void	ft_child(t_pipex **s, int i, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (-1 == pipe(pipe_fd))
		ft_errorer(&(*s));
	pid = fork();
	if (-1 == pid)
		ft_errorer(&(*s));
	if (pid == 0)
	{
		if (i)
			close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		if (-1 == execve((*s)->path[i], (*s)->cmd[i], envp))
			ft_errorer(&(*s));
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		waitpid(pid, NULL, 0);
	}
}

static void	ft_gate_pipex(t_pipex **s, char **argv, char **envp)
{
	int	i;

	i = 0;
	if (0 == ft_strncmp("here_doc", *argv, 9))
		ft_heredoc(s, *(++argv));
	else
		dup2((*s)->fd0, 0);
	while (i < (*s)->gnr - 1)
		ft_child(s, i++, envp);
	dup2((*s)->fd1, 1);
	if (-1 == execve((*s)->path[i], (*s)->cmd[i], envp))
		ft_errorer(s);
}

static int	ft_init(t_pipex **s, int comc)
{
	int	i;

	i = comc;
	*s = (t_pipex *)malloc(sizeof(t_pipex));
	if (!s)
		return (0);
	(*s)->path = (char **)malloc((1 + i) * sizeof(char *));
	if (!(*s)->path)
		return (0);
	(*s)->path[i] = NULL;
	(*s)->cmd = (char ***)malloc((1 + i) * sizeof(char **));
	if (!(*s)->cmd)
		return (0);
	(*s)->cmd[i] = NULL;
	(*s)->fd0 = 0;
	(*s)->fd1 = 1;
	(*s)->gnr = comc;
	return (1);
}

int	ft_pipex(int comc, char **argv, char **envp)
{
	pid_t	pid;
	t_pipex	*s;

	if (!ft_init(&s, comc))
		ft_errorer(&s);
	if (!ft_check_arg_b(&s, envp, argv))
		ft_errorer(&s);
	pid = fork();
	if (-1 == pid)
		ft_errorer(&s);
	if (0 == pid)
		ft_gate_pipex(&s, argv, envp);
	waitpid(pid, NULL, 0);
	//ft_freesher(&s);//mainproc dont die
	return (0);
}
