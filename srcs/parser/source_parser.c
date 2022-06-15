/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:58:20 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/15 16:23:44 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isbuildin(char *str)
{
	char	*ptr;
	int		buildin;

	ptr = ft_strchr(str, '|');
	buildin = 0;
	if (!ft_memcmp(str, "env", 4) \
		|| !ft_memcmp(str, "exit", 5) \
		|| !ft_memcmp(str, "export", 7) \
		|| !ft_memcmp(str, "unset", 6) \
		|| !ft_memcmp(str, "echo", 5) \
		|| !ft_memcmp(str, "pwd", 4) \
		|| !ft_memcmp(str, "cd", 3))
		buildin = 1;
	if (!ptr && buildin)
	{
		printf("---------is buildin\n");
		return (1);
	}
	return (0);
}

int	ft_count_ac(const char **spl)
{
	int		ac;
	int		i;
	char	*path;
	char	*tmp;

	ac = 0;
	i = 0;
	if (0 == ft_strncmp(spl[i], "here_doc", 9))
		i += 2;
	else
	{
		tmp = ft_strdup(spl[i]);
		path = ft_get_absolute_pth(tmp);
		if (0 == access(path, F_OK))//need func: try_open_file and del tmp && path
			ac = -1;
		free(path);
		free(tmp);
	}
	while (spl[i])
	{
		if (spl[i] && spl[i][0] != '>')
			ac++;
		if (spl[i][0] == '>')
			ac--;
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

char	**ft_union_cmd_flg(char ***av)
{
	char	**ptr;
	char	**ret;
	char	*tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	ptr = (*av);
	while (ptr[i])
	{
		if ('-' == ptr[i][0])
			j++;
		i++;
	}
	ret = (char **)ft_calloc(1 + ft_spllen((*av)) - j, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (ptr[i])
	{
		if (ptr[i] && ptr[i + 1] && '-' == ptr[i + 1][0])
		{
			k = 1;
			while (ptr[i] && ptr[i + k] && '-' == ptr[i + k][0])
			{
				if (1 == k)
					ret[j] = ft_strjoin(ptr[i], " ");
				else
				{
					tmp = ret[j];
					ret[j] = ft_strjoin(ret[j], " ");
					free(tmp);
				}
				tmp = ret[j];
				ret[j] = ft_strjoin(ret[j], ptr[i + k]);
				free(tmp);
				k++;
			}
			i += k;
		}
		else if (ptr[i])
			ret[j] = ft_strdup(ptr[i++]);//lost
		j++;
	}
	ret[j] = 0;
	ptr = ft_spldup(ret);//lost
	free(ret);
	free((*av));
	return (ptr);
}

char	**ft_union_cmd_file(char ***av)
{
	int		i;
	int		j;
	char	**ret;
	char	**ptr;

	j = 0;
	i = ft_spllen((*av));
	if (i == 1)
		return ((*av));
	ptr = (*av);
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	ret[i] = 0;
	i = 0;
	while (ptr [i])
	{
		if ((!ft_iscinstr((const char *)(ptr[i]), '>')) \
			&& ft_isfile(ptr[i + 1]))
		{
			ret[j] = ft_strjoinchar(ptr[i], ptr[i + 1], ' ');
			i++;
		}
		else
			ret[j] = ft_strdup(ptr[i]);
		i++;
		j++;
	}
	ret[j] = 0;
	ptr = ft_spldup(ret);
	free(ret);
	free((*av));
	return (ptr);
}
