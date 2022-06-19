/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:02:34 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/19 16:36:20 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_eject_first_part(char **find, char **tmp, char **cleaned)
{
	if ('<' == *((*find) + 1))
	{
		(*find) += 3;
		(*tmp) = ft_strndup((*find), \
			2 + ft_strnlen((*find) + 1, ' '));
		(*cleaned) = ft_strjoin("here_doc ", (*tmp));
		free(*tmp);
	}
	else
	{
		(*find) += 2;
		(*cleaned) = ft_strndup((*find), \
			1 + ft_strnlen((*find), ' '));
	}
}

char	*ft_inpfile(char **cmd)
{
	char	*find;
	char	*cleaned;
	char	*tmp;
	char	*ptr;

	find = ft_strnstr((*cmd), "<", ft_strnlen((*cmd), '|'));
	if (!find)
		find = ft_strnstr((*cmd), "<<", ft_strnlen((*cmd), '|'));
	if (find)
	{
		ft_eject_first_part(&find, &tmp, &cleaned);
		tmp = ft_strdup(find + 1 + ft_strnlen(find + 1, ' '));
		if ((*cmd[0]) != '<')
		{
			ptr = tmp;
			find = ft_strndup((*cmd), ft_strnlen((*cmd), ' '));
			tmp = ft_strjoin(find, ptr);
			ft_multifree(ptr, find, NULL);
		}
		free((*cmd));
		(*cmd) = tmp;
		printf("cmdCHECK:+%s+\n", (*cmd));
		ft_putendl_fd("-----SYSTEM---------", 2);
		ft_putstr_fd("redirect part:(", 2);
		ft_putstr_fd(cleaned, 2);
		ft_putendl_fd(") from inpfile", 2);
		ft_putendl_fd("---------SY---------", 2);
		return (cleaned);
	}
	return (NULL);
}

char	*ft_outfile(char **cmd)
{
	char	*find;
	char	*cleaned;
	char	*ptr;
	int		step;

	find = ft_strrnstr((*cmd), "> ", ft_strrnlen((*cmd), '|'));
	step = 3;
	if (!find)
	{
		find = ft_strrnstr((*cmd), ">> ", ft_strrnlen((*cmd), '|'));
		step = 4;
	}
	if (find)
	{
		find--;
		cleaned = ft_strndup(find, step + ft_strnlen(find + step, ' '));
		ptr = ft_strndup((*cmd), ft_strnlen((*cmd), '>'));
		find = ft_strdup(find + (step + ft_strnlen(find + step, ' ')));
		free((*cmd));
		(*cmd) = ft_strjoin(ptr, find);
		ft_multifree(ptr, find, NULL);
		ft_putendl_fd("-----SYSTEM---------", 2);
		ft_putstr_fd("redirect part:(", 2);
		ft_putstr_fd(cleaned, 2);
		ft_putendl_fd(") from outpfile", 2);
		ft_putendl_fd("---------SY---------", 2);
		return (cleaned);
	}
	return (NULL);
}
