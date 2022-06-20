/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:33:08 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/20 10:53:36 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_cleaner(char **cmd)
{
	char	*file;
	char	*end;
	char	*ptr;
	char	*tmp;

	if (!(*cmd))
		return (NULL);
	file = ft_inpfile(&(*cmd));
	end = ft_outfile(&(*cmd));
	tmp = ft_strjoin(file, (*cmd));
	ptr = tmp;
	tmp = ft_strjoin(ptr, end);
	if (!ft_strnstr(tmp, "echo ", 5))
		tmp = ft_deldoublec(&tmp, ' ');
	ft_multifree(ptr, end, file);
	free((*cmd));
	return (tmp);
}
