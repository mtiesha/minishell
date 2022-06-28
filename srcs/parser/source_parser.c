/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:58:20 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/28 17:54:25 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_source_bind(int *i, int *j, char ***ret, char ***ptr)
{
	char	*tmp;

	if ((*ptr)[(*i)] && (*ptr)[(*i) + 1] && !ft_isfile((*ptr)[(*i) + 1]) \
		&& (!ft_strncmp((*ptr)[(*i)], "echo", 4) \
		|| !ft_strncmp((*ptr)[(*i)], "mkdir", 5) \
		|| !ft_strncmp((*ptr)[(*i)], "touch", 5) \
		|| !ft_strncmp((*ptr)[(*i)], "grep", 4) \
		|| !ft_strncmp((*ptr)[(*i)], "chmod", 5)))
	{
		(*ret)[(*j)] = ft_strjoinchar((*ptr)[(*i)], (*ptr)[(*i) + 1], ' ');
		(*i)++;
		while ((*ptr)[(*i)] && (*ptr)[(*i) + 1] && !ft_isfile((*ptr)[(*i)]))
		{
			tmp = (*ret)[(*j)];
			(*ret)[(*j)] = ft_strjoinchar((*ret)[(*j)], (*ptr)[(*i) + 1], ' ');
			free(tmp);
			(*i)++;
		}
		(*i)++;
		(*j)++;
	}
}

int	ft_count_ac(const char **spl)
{
	int		ac;
	int		i;

	ac = 0;
	i = 0;
	if (0 == ft_strncmp(spl[i], "here_doc", 9))
		i += 2;
	else if (ft_isfile((char *)(spl[i])))
		ac = -1;
	while (spl[i])
	{
		if (spl[i] && (spl[i][0] != '>' || spl[i][0] != '<'))
			ac++;
		if (spl[i] && (spl[i][0] == '>' || spl[i][0] == '<'))
			ac -= 2;
		i++;
	}
	return (ac);
}

char	*ft_delete_pipes(t_src *s, int k)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = ft_strdup(s->cmds[k]);
	while (ptr[i])
	{
		if ('|' == ptr[i])
		{
			if (i > 0 && (ptr[i - 1] != ' '))
			{
				ptr = ft_charadd(&ptr, i, ' ');
				i++;
			}
			if (ptr[i + 1] == ' ')
				ptr = ft_chardel(&ptr, i + 1);
			ptr = ft_chardel(&ptr, i);
			i--;
		}
		i++;
	}
	free(s->cmds[k]);
	return (ptr);
}
