/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:46:26 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/29 06:46:26 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_set_red(t_pipex **s)
{
	int	k;

	k = 0;
	while (k <= ((*s)->gnr * 2) - 1)
		(*s)->red[k++] = -1;
}

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
	(*s)->ret_code = 0;
	(*s)->gnr = comc;
	(*s)->red = (int *)malloc((comc * 2) * sizeof(int));
	if (!(*s)->red)
		return (0);
	ft_set_red(s);
	return (1);
}

static int	ft_cast_cmd_path(t_pipex **s, char **envp, char **argv, int *i)
{
	(*s)->cmd[i[0]] = ft_split(argv[i[1]], ' ');
	if (!(*s)->cmd[i[0]])
		return (0);
	(*s)->path[i[0]] = ft_get_env_cmd(envp, (*s)->cmd[i[0]][0]);
	if (!(*s)->path[i[0]])
	{
		ft_putstr_fd((*s)->cmd[i[0]][0], 2);
		(*s)->ret_code = 127;
		return (0);
	}
	return (1);
}

static void	ft_set_dir(t_pipex **s, char ***argv, int *i, int *j)
{
	if ((*argv)[(*j)] && '<' == *((*argv)[(*j)]))
	{
		if ((*argv)[(*j)] && '<' == *((*argv)[(*j)]) && (*i) != 0)
		{
			(*s)->red[(*i) + (*i)] = ft_atoi((*argv)[(*j) + 1]);
			(*j) += 2;
		}
		else
			(*s)->red[(*i) + (*i)] = -1;
	}
	if ((*argv)[(*j)] && '>' == *((*argv)[(*j)]))
	{
		if ((*argv)[(*j)] && '>' == *((*argv)[(*j)]) \
			&& (*i) < (*s)->gnr - 1)
		{
			(*s)->red[(*i) + (*i) + 1] = ft_atoi((*argv)[(*j) + 1]);
			(*j) += 2;
		}
		else
			(*s)->red[(*i) + (*i) + 1] = -1;
	}
}

int	ft_check_arg_b(t_pipex **s, char **envp, char **argv)
{
	int	*i;

	i = (int *)ft_calloc(2, sizeof(int));
	if (0 != ft_strncmp("here_doc", argv[i[1]], 9))
		ft_open_first_file(s, argv);
	else
		i[1] += 2;
	if ((*s)->fd0 != 0)
		i[1] += 1;
	while (i[0] < (*s)->gnr)
	{
		ft_set_dir(s, &argv, &i[0], &i[1]);
		if (!ft_cast_cmd_path(s, envp, argv, i))
		{
			free(i);
			return (1);
		}
		i[1] += 1;
		ft_set_dir(s, &argv, &i[0], &i[1]);
		i[0]++;
	}
	if (argv[i[1]] && '>' == argv[i[1]][0])
		ft_open_last_file(s, argv, i[1]);
	free(i);
	return (0);
}
