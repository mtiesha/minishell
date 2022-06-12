/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 16:11:27 by marvin            #+#    #+#             */
/*   Updated: 2022/06/10 08:08:59 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	set_pipe_args(t_src *param, int i)
{
	char	**aux;
	int		j;
	int		k;

	j = 0;
	while (param->argv[i + j] && \
		ft_memcmp(param->argv[i + j], "|", 2))
		j++;
	aux = (char **)ft_calloc(sizeof(char *), j + 1);
	k = -1;
	while (++k < j)
		aux[k] = ft_strdup(param->argv[i + k]);
	param->argv = aux;
	param->argc = j;
}

static void	pipe_son(int *flag, int *fds, t_src *param, int pos)
{
	int		i;
	int		argc;
	char	**argv;

	signal(SIGINT, child_sig_handler);
	if (!fork())//child
	{
		if (!flag[0])
			dup2(fds[0], 0);
		if (!flag[1])
			dup2(fds[3], 1);
		i = 0;
		while (i < 4)
			close(fds[i++]);
		argc = param->argc;
		argv = param->argv;
		set_pipe_args(param, pos);
		check_command(param->str, param);
		ft_splfree(param->argv);
		param->argc = argc;
		param->argv = argv;
		exit(param->ret);
	}
}

static void	switch_pipes(int *fds)
{
	close(fds[0]);//parent
	close(fds[1]);
	fds[0] = fds[2];
	fds[1] = fds[3];
	pipe(fds + 2);
}

static int	check_pipe(int *fds, t_src *param)
{
	int		sons;
	int		*flag;
	int		i;
	int		j;

	sons = 0;
	flag = (int *)malloc(sizeof(int) * 2);
	flag[0] = 1;
	flag[1] = 0;
	j = 0;
	while (param->argv[j])
	{
		i = 0;
		while (param->argv[j + i] &&
		ft_memcmp(param->argv[j + i], "|", 2))
			i++;
		flag[1] = (!param->argv[i + j]) ? 1 : 0;
		pipe_son(flag, fds, param, j);
		sons++;
		flag[0] = 0;
		switch_pipes(fds);
		j += !param->argv[j + i] ? i : i + 1;
	}
	free(flag);
	return (sons);
}

void	command_or_pipe(t_src *src, int j)
{
	int	fds[4];
	int	std_out;
	int	sons;
	int	i;

	std_out = dup(0);
	i = 0;
	printf("--------------------\n");
	printf("SYSTEM INFO [COMANDORPIPE]\n");
	printf("ARGV - ");
	while (src->argv[i])
	{
		printf("%d:%s | ", i, src->argv[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf("ARGC - %d \n", src->argc);
	printf("--------------------\n\n");
	// while (src->argv[i] && ft_memcmp(src->argv[i], "|", 2))
	// 	i++; maybe delete
	if (!src->argv[i])
		src->envp = check_command(src->cmds[j], src);
	else if (src->cmds[j])
	{
		pipe(fds);
		pipe(fds + 2);
		sons = check_pipe(fds, src);
		while (sons-- > 0)
			wait(&src->ret);
		src->ret /= 256;
		i = -1;
		while (++i < 4)
			close(fds[i]);
	}
	dup2(std_out, 0);
}
