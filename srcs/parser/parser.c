/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:16:52 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/15 17:36:09 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parser(t_src *src)
{
	int		i;
	int		buildin;
	char	*ptr;

	if (!ft_check_wrong_pipe(src))
		return ;
	src->str = ft_deldoublec(&src->str, ' ');
	ptr = src->str;
	src->str = ft_strtrim(src->str, ";| +-");
	free(ptr);
	src->cmds = ft_split(src->str, ';');
	i = 0;
	while (src->cmds[i])
	{
		buildin = ft_isbuildin(src->cmds[i]);
		printf("cmd[0] start: +%s+\n", src->cmds[i]);
		src->cmds[i] = ft_delete_pipes(&(*src), i);
		printf("after delete pipes: +%s+\n", src->cmds[i]);
		src->cmds[i] = ft_cleaner(&src->cmds[i]);
		printf("after cleaner: +%s+\n", src->cmds[i]);
		src->argv = ft_split(src->cmds[i], ' ');
		src->argv = ft_union_cmd_flg(&src->argv);
		src->argv = ft_union_cmd_file(&src->argv);
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
	free(src->str);
	src->str = NULL;
	ft_splfree(src->cmds);
}
