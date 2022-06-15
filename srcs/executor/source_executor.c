/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 07:03:00 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/15 17:54:25 by mtiesha          ###   ########.fr       */
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

	if (file && !(file[0] == '/' || file[0] == '.'))
		path = ft_get_absolute_pth(file);
	else if (file)
		path = file;
	if (0 == access(path, F_OK))
	{
		ft_putstr_fd(path, 2);
		ft_putendl_fd("   <---  file who check 1", 2);
		free(path);
		return (1);
	}
	if (file)
		free(path);
	ft_putendl_fd("   <---  file who check 0", 2);
	return (0);
}
