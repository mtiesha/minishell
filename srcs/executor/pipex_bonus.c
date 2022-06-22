/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:23:47 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/22 07:29:07 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_grandson(int *pipe_fd, int i, t_pipex **s, char **envp)
{
	if (i)
		close(pipe_fd[0]);
	if (-1 == (*s)->red[i + i + 1])
		dup2(pipe_fd[1], 1);
	else
		dup2((*s)->red[i + i + 1], 1);
	if (-1 == execve((*s)->path[i], (*s)->cmd[i], envp))
		ft_errorer(s, "Execve error [ch]");
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
		ft_grandson(pipe_fd, i, s, envp);
	else
	{
		close(pipe_fd[1]);
		if (-1 == (*s)->red[i + i])
			dup2(pipe_fd[0], 0);
		else
			dup2((*s)->red[i + i], 0);
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
	printf("@@@@@____CHILD_WORK_____@@@@@@\n");
	while (i < (*s)->gnr - 1)
		ft_child(s, i++, envp);
	printf("@@@@@____CHILD_WORK_____@@@@@@\n");
	dup2((*s)->fd1, 1);
	if (-1 == execve((*s)->path[i], (*s)->cmd[i], envp))
		ft_errorer(s, "Execve error [gt]");
}

int	ft_pipex(int comc, char **argv, char **envp)
{
	t_pipex	*s;
	pid_t	pid;
	int		ret_code;

	ft_putendl_fd("------AV--------", 2);
	ft_putspl_fd(argv, 2);
	ft_putendl_fd("------AV--------", 2);
	if (!ft_init_p(&s, comc))
		ft_errorer(&s, "Init pipex error");
	if (!ft_check_arg_b(&s, envp, argv))
	{
		ft_errorer(&s, " Command not found");
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
