/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:46:26 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/19 13:10:24 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_init_p(t_pipex **s, int comc)
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

static void	ft_open_last_file(t_pipex **s, char **argv)
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

static void	ft_open_first_file(t_pipex **s, char **argv)
{
	if (ft_isfile((*argv)))
	{
		(*s)->fd0 = open(*(argv), O_RDONLY, 0777);
		if (-1 == (*s)->fd0)
			ft_errorer(s, NULL);
	}
}

int	ft_check_arg_b(t_pipex **s, char **envp, char **argv)
{
	int	i;

	i = 0;
	if (0 != ft_strncmp("here_doc", *(argv), 9))
		ft_open_first_file(s, argv);
	else
		argv += 2;
	if ((*s)->fd0 != 0)
		argv++;
	printf("~fd:%d %d\n", (*s)->fd0, (*s)->fd1);
	while (i < (*s)->gnr)
	{
		printf("cmd[%d]: %s\n", i, *(argv));
		(*s)->cmd[i] = ft_split(*(argv++), ' ');
		if (!(*s)->cmd[i])
			return (0);
		(*s)->path[i] = ft_get_env_cmd(envp, (*s)->cmd[i][0]);
		if (!(*s)->path[i])
		{
			ft_putstr_fd((*s)->cmd[i][0], 2);
			return (0);
		}
		i++;
	}
	if (*(argv) && '>' == *(argv[0]))
		ft_open_last_file(s, argv);
	return (1);
}
