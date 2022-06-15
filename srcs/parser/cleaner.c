/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:33:08 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/15 17:01:52 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_inpfile(char **cmd)
{
	char	*find;
	char	*cleaned;
	char	*tmp;
	char	*ptr;
	int		step;

	find = ft_strnstr((*cmd), "<", ft_strlen((*cmd)));
	if (!find)
		find = ft_strnstr((*cmd), "<<", ft_strlen((*cmd)));
	if (find)
	{
		if ('<' == *(find + 1))
		{
			step = 3;
			find += step;
			tmp = ft_strndup(find, 2 + ft_strnlen(find + 1, ' '));
			cleaned = ft_strjoin("here_doc ", tmp);
		}
		else
		{
			step = 2;// ls < f1 || < f1 ls |
			find += step;
			cleaned = ft_strndup(find, 1 + ft_strnlen(find, ' '));
		}
		tmp = ft_strdup(find + 1 + ft_strnlen(find + 1, ' '));
		if ((*cmd[0]) != '<')
		{
			ptr = tmp;
			find = ft_strndup((*cmd), ft_strnlen((*cmd), ' '));
			tmp = ft_strjoin(find, ptr);
			free(ptr);
			free(find);
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

static char	*ft_outfile(char **cmd)
{
	char	*find;
	char	*cleaned;
	char	*ptr;
	int		step;

	find = ft_strnstr((*cmd), ">", ft_strlen((*cmd)));
	step = 3;
	if (!find)
	{
		find = ft_strnstr((*cmd), ">>", ft_strlen((*cmd)));
		step = 4;
	}
	if (find)// wc >> f2 || >> f2 wc cleaned[ >> f2]
	{
		find--;
//		if (' ' == (*find + step))
		cleaned = ft_strndup(find, step + ft_strnlen(find + step, ' '));
//		else
//`			cleaned = ft_strndup(find, step + ft_strlen(find + step));
		ptr = ft_strndup((*cmd), ft_strnlen((*cmd), '>'));
		find = ft_strdup(find + (step + ft_strnlen(find + step, ' ')));
		free((*cmd));
		(*cmd) = ft_strjoin(ptr, find);
		free(ptr);
		free(find);
		ft_putendl_fd("-----SYSTEM---------", 2);
		ft_putstr_fd("redirect part:(", 2);
		ft_putstr_fd(cleaned, 2);
		ft_putendl_fd(") from outpfile", 2);
		ft_putendl_fd("---------SY---------", 2);
		return (cleaned);
	}
	return (NULL);
}

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
	tmp = ft_deldoublec(&tmp, ' ');
	free(ptr);
	free(end);
	free(file);
	free((*cmd));
	return (tmp);
}
