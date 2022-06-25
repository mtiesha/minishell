/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 12:03:39 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/25 15:02:30 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_norm_cheat_u(char **tmp, char ***ret, int j)
{
	(*tmp) = ft_strdup(" ");
	(*ret)[j] = ft_strjoinfree(&(*ret)[j], &(*tmp), 2);
}

static void	ft_union_flg_logic(char ***ret, char ***ptr, int j, int i)
{
	char	*tmp;
	int		k;

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
					ft_norm_cheat_u(&tmp, &(*ret), j);
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
	ft_union_flg_logic(&ret, &ptr, j, i);
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
		ft_source_bind(&i, &j, &(*ret), &(*ptr));
		printf("s---tri:%s\n", (*ptr)[i]);
		if ((*ptr)[i] && (!ft_iscinstr((const char *)(*ptr)[i], '>') \
			&& ft_isfile((*ptr)[i + 1])) && \
				(!ft_iscinstr((const char *)(*ptr)[i], '<')))
		{
			printf("JOIN\n");
			(*ret)[j] = ft_strjoinchar((*ptr)[i], (*ptr)[i + 1], ' ');
			i++;
		}
		else if ((*ptr)[i])
		{
			(*ret)[j] = ft_strdup((*ptr)[i]);
			printf("NEJOIN\n");
		}
		if ((*ptr)[i])
			i++;
		j++;
	}
}

char	**ft_union_cmd_file(char **av)
{
	int		i;
	char	**ret;
	char	**ptr;

	printf("UNIONFILE-+++++++++++\n");
	i = ft_spllen(av);
	if (i == 1)
		return (ft_spldup(av));
	ptr = av;
	ret = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	ft_union_cmd_file_logic(&ret, &ptr);
	ptr = ft_spldup(ret);
	ft_putendl_fd("masiv4ik na vihode:", 2);
	ft_putspl_fd(ptr, 2);
	ft_splfree(ret);
	printf("UNIONFILE-+++++++++++\n");
	return (ptr);
}
