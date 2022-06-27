/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:16:52 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/27 18:47:16 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**ft_cast_av(t_src *src, int i, int buildin)
{
	char	**ptr;
	char	**tmp;
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
	ft_putendl_fd("---cmds[i] split---", 2);
	ft_putspl_fd(ptr, 2);
	ft_putendl_fd("---cmds[i] split---", 2);
	if (!buildin)
	{
		tmp = ft_union_cmd_flg(ptr);
		ft_splfree(ptr);
		src->argv = ft_union_cmd_file(tmp);
		ft_splfree(tmp);
	}
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
	printf("prser] cmd[0] start: +%s+\n", src->cmds[i]);
	src->cmds[i] = ft_cleaner(&src->cmds[i]);
	printf("prser] after cleaner: +%s+\n", src->cmds[i]);
	src->cmds[i] = ft_delete_pipes(&(*src), i);
	printf("prser] after delete pipes: +%s+\n", src->cmds[i]);
	src->argv = ft_cast_av(src, i, buildin);
	src->argc = ft_count_ac((const char **)(src->argv));
	if (buildin && ft_strnstr(src->cmds[i], \
		"echo", ft_strlen(src->cmds[i])))
		src->ret = ft_exec_echo(src, i);
	else if (buildin)
		src->ret = ft_gate_binary(src);
	else
	{
		printf("-------------PIPEX-------------\n");
		src->ret = ft_pipex(src->argc, src->argv, src->export);
		printf("-------------PIPEX-------------\n");
	}
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
	printf("MASIK\n");
	ft_putspl_fd(src->cmds, 2);
	printf("MASIK\n");
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
