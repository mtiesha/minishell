/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 10:27:57 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/29 06:46:38 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_is_valid_path(const char **envp)
{
	if (*envp == 0)
		return (0);
	while (0 != ft_strncmp(*envp, "PATH", 4))
		envp++;
	if (*envp == 0)
		return (0);
	return (1);
}

static char	*ft_get_paths(char **envp)
{
	char	*ptr;

	if (!ft_is_valid_path((const char **)(envp)))
		return (NULL);
	while (0 != ft_strncmp(*envp, "PATH", 4))
		envp++;
	ptr = *envp;
	return (ptr + 5);
}

static void	ft_strchange_f_c(char **str1, const char *str2, int trig)
{
	char	*tmp;

	tmp = *str1;
	*str1 = ft_strjoin(*str1, str2);
	if (!*str1)
		free(tmp);
	else if (trig)
		free(tmp);
}

char	*ft_get_env_cmd(char **envp, char *command)
{
	char	**strs;
	char	*str;
	char	**first;

	strs = ft_split(ft_get_paths(envp), ':');
	if (!strs)
		return (NULL);
	first = strs;
	while (*strs)
	{
		str = ft_strjoin(*strs, "/");
		if (!str)
			return (NULL);
		ft_strchange_f_c(&str, command, 1);
		if (0 == access(str, F_OK))
		{
			ft_splfree(first);
			return (str);
		}
		free(str);
		strs++;
	}
	ft_splfree(first);
	return (NULL);
}
