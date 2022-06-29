/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:16:52 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/29 06:43:21 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_not_build(t_src *src, char ***ptr)
{
	char	**tmp;

	tmp = NULL;
	tmp = ft_union_cmd_flg((*ptr));
	ft_splfree((*ptr));
	src->argv = ft_union_cmd_file(tmp);
	ft_splfree(tmp);
}

static char	**ft_cast_av(t_src *src, int i, int buildin)
{
	char	**ptr;
	char	*ptr2[2];
	char	*tmp2;

	if (!ft_strchr(src->cmds[i], '\"') && !ft_strrchr(src->cmds[i], '\"'))
		ptr = ft_split(src->cmds[i], ' ');
	else
	{
		ptr2[0] = ft_strdup(src->cmds[i]);
		tmp2 = ptr2[0];
		ptr2[0] = ft_strtrim(tmp2, " ");
		free(tmp2);
		ptr2[1] = 0;
		ptr = ft_spldup(ptr2);
		free(ptr2[0]);
	}
	if (!buildin)
		ft_not_build(src, &ptr);
	else
		src->argv = ptr;
	return (src->argv);
}

static void	ft_parsing_logic(t_src *src, int i)
{
	int	buildin;

	buildin = ft_isbuildin(src->cmds[i]);
	if (!buildin)
		src->str = ft_deldoublec(&src->str, ' ');
	src->cmds[i] = ft_cleaner(&src->cmds[i]);
	src->cmds[i] = ft_delete_pipes(&(*src), i);
	src->argv = ft_cast_av(src, i, buildin);
	src->argc = ft_count_ac((const char **)(src->argv));
	if (buildin && ft_strnstr(src->cmds[i], \
		"echo", ft_strlen(src->cmds[i])))
		src->ret = ft_exec_echo(src, i);
	else if (buildin)
		src->ret = ft_gate_binary(src);
	else
		src->ret = ft_pipex(src->argc, src->argv, src->export);
	ft_splfree(src->argv);
}

void	parser(t_src *src)
{
	int		i;
	char	*ptr;

	i = -1;
	if (!ft_check_wrong_pipe(src))
		return ;
	ptr = src->str;
	src->str = ft_strtrim(src->str, " ;| +-");
	free(ptr);
	src->cmds = ft_split(src->str, '&');
	while (src->cmds[++i] && 0 == src->ret)
	{
		ptr = src->cmds[i];
		src->cmds[i] = ft_strtrim(src->cmds[i], " ;| +-");
		free(ptr);
		ft_parsing_logic(src, i);
	}
	free(src->str);
	src->str = NULL;
	ft_splfree(src->cmds);
}
