/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:03:39 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/18 14:25:33 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_union_flg_logic(char ***ret, char ***ptr, int j, int i, int k)
{
	char	*tmp;

	while ((*ptr)[i])
	{
		if ((*ptr)[i] && (*ptr)[i + 1] && '-' == (*ptr)[i + 1][0])
		{
			k = 1;
			while ((*ptr)[i] && (*ptr)[i + k] && '-' == (*ptr)[i + k][0])
			{
				if (1 == k)
					(*ret)[j] = ft_strjoin((*ptr)[i], " ");
				else
				{
					tmp = ft_strdup(" ");
					(*ret)[j] = ft_strjoinfree(&(*ret)[j], &tmp, 2);
				}
				(*ret)[j] = ft_strjoinfree(&(*ret)[j], &(*ptr)[i + k], 0);
				k++;
			}
			i += k;
		}
		else if ((*ptr)[i])
			(*ret)[j] = ft_strdup((*ptr)[i++]);
		j++;
	}
}

char	**ft_union_cmd_flg(char **av)
{
	int		i;
	int		j;
	int		k;
	char	**ptr;
	char	**ret;

	j = 0;
	i = 0;
	ptr = av;
	while (ptr[i])
	{
		if ('-' == ptr[i][0])
			j++;
		i++;
	}
	ret = (char **)ft_calloc(1 + ft_spllen(av) - j, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	j = 0;
	i = 0;
	k = 0;
	ft_union_flg_logic(&ret, &ptr, j, i, k);
	ptr = ft_spldup(ret);
	ft_splfree(ret);
	return (ptr);
}

static void	ft_union_cmd_file_logic(char ***ret, char ***ptr)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while ((*ptr)[i])
	{
		if (!ft_iscinstr((const char *)(*ptr)[i], '>') \
			&& ft_isfile((*ptr)[i + 1]))
		{
			(*ret)[j] = ft_strjoinchar((*ptr)[i], (*ptr)[i + 1], ' ');
			i++;
		}
		else
			(*ret)[j] = ft_strdup((*ptr)[i]);
		i++;
		j++;
	}
}

char	**ft_union_cmd_file(char **av)
{
	int		i;
	char	**ret;
	char	**ptr;

	i = ft_spllen(av);
	if (i == 1)
		return (ft_spldup(av));
	ptr = av;
	ret = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	ft_union_cmd_file_logic(&ret, &ptr);
	ptr = ft_spldup(ret);
	ft_splfree(ret);
	return (ptr);
}
