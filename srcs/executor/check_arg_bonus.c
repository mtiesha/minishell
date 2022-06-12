/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:46:26 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/11 20:49:26 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_get_absolute_pth(char *file)
{
	char	cwd[4097];
	char	*path;
	char	*tmp;

	getcwd(cwd, 4096);
	path = ft_strjoin(cwd, "/");
	tmp = ft_strjoin(path, file);
	free(path);
	return (tmp);
}

static void	ft_open_last_file(t_pipex **s, char **argv)
{
	if (0 == ft_strncmp(">", *(argv), 2))
	{
		printf("~fileend:%s\n", *(1 + argv));
		(*s)->fd1 = open(*(++argv), O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if ((*s)->fd1 == -1)
			ft_errorer(s);
	}
	else if (0 == ft_strncmp(">>", *(argv), 3))
	{
		(*s)->fd1 = open(*(++argv), O_WRONLY | O_APPEND | O_CREAT, 0777);
		if ((*s)->fd1 == -1)
			ft_errorer(s);
	}
}

static void	ft_open_first_file(t_pipex **s, char **argv)
{
	char	*path;

	if (*(argv) && !(*(argv[0]) == '/' || *(argv[0]) == '.'))
		path = ft_get_absolute_pth(*(argv));
	else if (*(argv))
		path = *(argv);
	if (0 == access(path, F_OK))
	{
		(*s)->fd0 = open(*(argv), O_RDONLY, 0777);
		if (-1 == (*s)->fd0)
			ft_errorer(s);
	}
	if (*(argv))
		free(path);
}

int	ft_check_arg_b(t_pipex **s, char **envp, char **argv)
{
	int	i;

	i = 0;
	ft_putendl_fd("-------argv------", 2);
	ft_putspl_fd(argv, 2);
	ft_putendl_fd("-------conec------", 2);
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
			ft_errorer(s);
		(*s)->path[i] = ft_get_env_cmd(envp, (*s)->cmd[i][0]);
		if (!(*s)->path[i])
			ft_errorer(s);
		i++;
	}
	if (*(argv) && '>' == *(argv[0]))
		ft_open_last_file(s, argv);
	return (1);
}
