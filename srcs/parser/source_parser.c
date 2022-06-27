/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:58:20 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/27 13:05:08 by mtiesha          ###   ########.fr       */
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
		printf("i:%d j:%d ptr1:%s+ ptr1+1:%s+\n", (*i), (*j), (*ptr)[(*i)], (*ptr)[(*i) + 1]);
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

// static char	**ft_spljoin(char **spl, char *str1, char *str2)
// {
// 	char	**ret;
// 	char	**tmp;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	tmp = (char **)ft_calloc(ft_spllen(spl), sizeof(char *));
// 	while (spl[i])
// 	{
// 		if (!ft_strncmp(spl[i], str1, ft_strlen(spl[i])))
// 		{
// 			tmp[j] = ft_strjoinchar(str1, str2, ' ');
// 			i++;
// 		}
// 		else
// 			tmp[j] = ft_strdup(spl[i]);
// 		i++;
// 		j++;
// 	}
// 	ret = ft_spldup(tmp);
// 	free(tmp);
// 	return (ret);
// }

// char	**ft_ressurection_spl_q(char **spl)
// {
// 	int		i;
// 	char	**ptr;
// 	char	**ret;
// // koroche vot eta nada dlya
// // "ls -la
// //  wc -l"
// // skley obratno
// 	i = 0;
// 	while (spl[i] && spl[i + 1])
// 	{
// 		if (('\"' == spl[i][0]
// 			&& '\"' == spl[i + 1][ft_strlen(spl[i + 1]) - 1])
// 			|| ('\'' == spl[i][0]
// 			&& '\'' == spl[i + 1][ft_strlen(spl[i + 1]) - 1]))
// 		{
// 			if (!ret)
// 				ret = ft_spljoin(spl, spl[i], spl[i + 1]);
// 			else
// 			{
// 				ptr = ret;
// 				ret = ft_spljoin(ret, spl[i], spl[i + 1]);
// 				ft_splfree(ptr);
// 			}
// 		}
// 		i++;
// 	}
// 	if (ret)
// 		ft_splfree(spl);
// 	else
// 		ret = spl;
// 	return (ret);
// }

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
	printf("arg_count:%d\n", ac);
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
