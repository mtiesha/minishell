/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:23:47 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/27 11:27:36 by mtiesha          ###   ########.fr       */
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
	{
		printf("GS DUP in to file [%d]\n", (*s)->red[i + i + 1]);
		dup2((*s)->red[i + i + 1], 1);
	}
	if (-1 == execve((*s)->path[i], (*s)->cmd[i], envp))
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_errorer(s, " : Execve error [gs]");
		exit(127);
	}
}

static int	ft_child(t_pipex **s, int i, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		k;

	k = 0;
	if (-1 == pipe(pipe_fd))
		return (ft_errorer(&(*s), "Pipe error [ch]"));
	pid = fork();
	if (-1 == pid)
		return (ft_errorer(&(*s), "Fork error [ch]"));
	if (pid == 0)
		ft_grandson(pipe_fd, i, s, envp);
	else
	{
		close(pipe_fd[1]);
		if (-1 == (*s)->red[i + i + 2])
			dup2(pipe_fd[0], 0);
		else
		{
			printf("CHILD DUP in to file [%d]\n", (*s)->red[i + i + 2]);
			dup2((*s)->red[i + i + 2], 0);
		}
		while (k <= ((*s)->gnr * 2) - 1)
			printf("REDMASS:%d\n", (*s)->red[k++]);
		printf("I:%d\n", i);
		waitpid(pid, &(*s)->ret_code, 0);
	}
	return ((*s)->ret_code);
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
	while (i < (*s)->gnr - 1 && 0 == (*s)->ret_code)
		(*s)->ret_code = ft_child(s, i++, envp);
	printf("@@@@@____CHILD_WORK_____@@@@@@\n");
	dup2((*s)->fd1, 1);
	if (0 != (*s)->ret_code)
		exit (((*s)->ret_code >> 8) & 0x000000ff);
	else if (-1 == execve((*s)->path[i], (*s)->cmd[i], envp))
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_errorer(s, ": Execve error [gt]");
		exit(127);
	}
}

int	ft_pipex(int comc, char **argv, char **envp)
{
	t_pipex	*s;
	pid_t	pid;
	int		ret_code_l;

	ft_putendl_fd("------AV--------", 2);
	ft_putspl_fd(argv, 2);
	ft_putendl_fd("------AV--------", 2);
	if (!ft_init_p(&s, comc))
		return (ft_errorer(&s, "Init pipex error"));
	if (ft_check_arg_b(&s, envp, argv))
		return (ft_errorer(&s, " Command not found"));
	pid = fork();
	if (0 == pid)
	{
		ft_signal_cast(0);
		ft_gate_pipex(&s, argv, envp);
	}
	else if (-1 != pid && 0 != pid)
		waitpid(pid, &s->ret_code, 0);
	printf("RETCODE:%d\n", s->ret_code);
	ret_code_l = s->ret_code;
	ft_freesher(&s);
	return (ret_code_l);
}
