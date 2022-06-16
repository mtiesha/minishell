/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:16:52 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/16 06:56:49 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**ft_cast_av(t_src *src, int i)
{
	char	**ptr;
	char	**tmp;

	ptr = ft_split(src->cmds[i], ' ');
	ft_putendl_fd("---cmds[i] split---", 2);
	ft_putspl_fd(ptr, 2);
	ft_putendl_fd("---cmds[i] split---", 2);
	tmp = ft_union_cmd_flg(ptr);
	free(ptr);
	src->argv = ft_union_cmd_file(tmp);
	free(tmp);
	return (src->argv);
}

static void	ft_parsing_logic(t_src *src)
{
	int	i;
	int	buildin;

	i = 0;
	while (src->cmds[i])
	{
		buildin = ft_isbuildin(src->cmds[i]);
		printf("cmd[0] start: +%s+\n", src->cmds[i]);
		src->cmds[i] = ft_delete_pipes(&(*src), i);
		printf("after delete pipes: +%s+\n", src->cmds[i]);
		src->cmds[i] = ft_cleaner(&src->cmds[i]);
		printf("after cleaner: +%s+\n", src->cmds[i]);
		src->argv = ft_cast_av(src, i);
		src->argc = ft_count_ac((const char **)(src->argv));
		if (buildin)
			src->ret = ft_gate_binary(src);
		else
		{
			printf("-------------PIPEX-------------\n");
			src->ret = ft_pipex(src->argc, src->argv, src->export);
			printf("-------------PIPEX-------------\n");
		}
		ft_splfree(src->argv);
		i++;
	}
}

void	parser(t_src *src)
{
	char	*ptr;

	if (!ft_check_wrong_pipe(src))
		return ;
	src->str = ft_deldoublec(&src->str, ' ');
	ptr = src->str;
	src->str = ft_strtrim(src->str, ";| +-");
	free(ptr);
	src->cmds = ft_split(src->str, ';');
	ft_parsing_logic(src);
	free(src->str);
	src->str = NULL;
	ft_splfree(src->cmds);
}
