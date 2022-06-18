/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:23:47 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/18 11:43:05 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_init(t_pipex **s, int comc)
{
	int	i;

	i = comc;
	*s = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
	if (!s)
		return (0);
	(*s)->path = NULL;
	(*s)->cmd = NULL;
	(*s)->path = (char **)ft_calloc((1 + i), sizeof(char *));
	if (!(*s)->path)
		return (0);
	(*s)->path[i] = NULL;
	(*s)->cmd = (char ***)ft_calloc((1 + i), sizeof(char **));
	if (!(*s)->cmd)
		return (0);
	(*s)->cmd[i] = NULL;
	(*s)->fd0 = 0;
	(*s)->fd1 = 1;
	(*s)->gnr = comc;
	return (1);
}

void	ft_heredoc(t_pipex **s, char *stop)
{
	pid_t	pid;
	int		pipe_fd[2];
	char	*line;

	if (-1 == pipe(pipe_fd))
		ft_errorer(s, "Pipe error [hd]");
	pid = fork();
	if (-1 == pid)
		ft_errorer(&(*s), "Fork error [ch]");
	if (pid == 0)
	{
		close(pipe_fd[0]);
		while (ft_gnl_sh(&line, 10000, 0))
		{
			if (0 == ft_strncmp(line, stop, ft_strlen(stop)))
			{
				ft_freesher(s);
				free(line);
				exit(0);
			}
			write(pipe_fd[1], line, ft_strlen(line));
			free(line);
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
		ft_errorer(&(*s), "Pipe error [ch]");
	pid = fork();
	if (-1 == pid)
		ft_errorer(&(*s), "Fork error [ch]");
	if (pid == 0)
	{
		if (i)
			close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		if (-1 == execve((*s)->path[i], (*s)->cmd[i], envp))
			ft_errorer(s, "Execve error [ch]");
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
		ft_errorer(s, "Execve error [gt]");
}

int	ft_pipex(int comc, char **argv, char **envp)
{
	pid_t	pid;
	t_pipex	*s;
	int		ret_code;

	ret_code = 0;
	ft_putendl_fd("------AV--------", 2);
	ft_putspl_fd(argv, 2);
	ft_putendl_fd("------AV--------", 2);
	if (!ft_init(&s, comc))
		ft_errorer(&s, "Init pipex error");
	if (!ft_check_arg_b(&s, envp, argv))
	{
		ft_errorer(&s, "Command not found");
		return (1);
	}
	pid = fork();
	if (-1 == pid)
		ft_errorer(&s, "Fork error [mn]");
	if (0 == pid)
	{
		ft_signal_cast(0);
		ft_gate_pipex(&s, argv, envp);
	}
	else if (-1 != pid && 0 != pid)
		waitpid(pid, &ret_code, 0);
	ft_freesher(&s);
	return (ret_code);
}
