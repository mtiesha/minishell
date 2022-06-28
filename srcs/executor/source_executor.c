/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 07:03:00 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/28 17:30:40 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_get_absolute_pth(char *file)
{
	char	cwd[4242];
	char	*path;
	char	*tmp;

	getcwd(cwd, 4221);
	path = ft_strjoin(cwd, "/");
	tmp = ft_strjoin(path, file);
	free(path);
	return (tmp);
}

static int	ft_if_open(char *path, int mask)
{
	int	fd;

	fd = -1;
	if (0 == mask)
	{
		if (ft_isfile(path))
			fd = open(path, O_RDONLY, 0777);
		else
			return (fd);
	}
	else if (1 == mask)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (2 == mask)
		fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0777);
	return (fd);
}

int	ft_try_open_file(char *file, int mask)
{
	char	*path;
	int		free_flag;
	int		fd;

	free_flag = 1;
	if (file && !(file[0] == '/' || file[0] == '.'))
		path = ft_get_absolute_pth(file);
	else if (file)
	{
		path = file;
		free_flag = 0;
	}
	fd = ft_if_open(path, mask);
	if (-1 == fd)
	{
		if (free_flag)
			free(path);
		return (fd);
	}
	if (file && free_flag)
		free(path);
	return (fd);
}

int	ft_isfile(char *file)
{
	char	*path;
	int		free_flag;

	free_flag = 1;
	if (file && !(file[0] == '/' || file[0] == '.'))
		path = ft_get_absolute_pth(file);
	else if (file)
	{
		path = file;
		free_flag = 0;
	}
	if (0 == access(path, F_OK))
	{
		if (free_flag)
			free(path);
		return (1);
	}
	if (file && free_flag)
		free(path);
	return (0);
}
