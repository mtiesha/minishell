/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 07:03:00 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/16 18:48:40 by mtiesha          ###   ########.fr       */
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
		ft_putstr_fd(path, 2);
		ft_putendl_fd("   <---  file who check 1", 2);
		if (free_flag)
			free(path);
		return (1);
	}
	if (file && free_flag)
		free(path);
	ft_putendl_fd("   <---  file who check 0", 2);
	return (0);
}
