/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 14:12:39 by marvin            #+#    #+#             */
/*   Updated: 2022/06/12 15:58:56 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
static int	change_env(int i, int braces, char **str, t_src *param)
{
	int		len;
	char	*bef;
	char	*aft;
	char	*env;
	char	*aux;

	braces = ((*str)[i + 1] == '{') ? 1 : 0;
	len = (ft_strlen_char(*str + i + 1, ':') < ft_strlen_env(*str + i + 1)) ?
	ft_strlen_char(*str + i + 1, ':') + 1 :
	ft_strlen_env(*str + i + 1) + 1 + braces;
	bef = ft_strndup(*str, i);
	aux = ft_strndup(*str + i + 1 + braces, len - 1 - braces * 2);
	env = (!ft_memcmp(aux, "?", 2)) ? ft_itoa(param->ret) : 0;
	aft = ft_strdup(*str + i + len);
	env = (!env) ? ft_strdup(get_env(param->envp, aux)) : env;
	free(aux);
	len = ft_strlen(env);
	aux = ft_strjoin(bef, env);
	free(bef);
	free(env);
	free(*str);
	*str = ft_strjoin(aux, aft);
	free(aux);
	free(aft);
	return (len);
}

static int	check_quotes(char **str, int *i)
{//shit.. rewrite
	(*i)++;
	while ((*str)[*i] && ((*str)[*i] != '\''))
	{
		(*i)++;
	}
	if (!(*str)[*i])
	{
		ft_putstr_fd("Non finished quotes\n", 2);
		return (1);
	}
	return (0);
}

static int	check_env(char **str, t_src *param)
{
	int	i;
	int	braces;

	i = 0;
	braces = 0;
	while ((*str) && (*str)[i])
	{
		if ((*str)[i] == '\'' && check_quotes(str, &i))
			return (1);
		if ((*str)[i] && (*str)[i] == '\\')
		{
			if ((*str)[i + 1] == '$')
				rm_char(str, i);
			if ((*str)[i + 1])
				i++;
		}
		else if ((*str)[i] == '$' && !(!(*str)[i + 1] ||
		ft_isspace((*str)[i + 1]) || (*str)[i + 1] == '\'' ||
		(*str)[i + 1] == '"' || (*str)[i + 1] == '/'))
			i += change_env(i, braces, str, param) - 1;
		i++;
	}
	return (0);
}

static int	check_semicolon(t_src *s)
{
	if (!s->str || !ft_memcmp(s->str, ";", 2))
	{
		if (s->str)
		{
			ft_putstr_fd(MES_ERR_SYNT_S, 2);
			s->ret = 2;
		}
		free(s->str);
		s->str = 0;
		return (1);
	}
	return (0);
}
*/
/*
static char	*ft_remove_token(char **find)
{
	int		redirec;
	int		space;
	char	*ret;

	redirec = 1;
	space = 1;
	if ('<' == ((*(*find) + 1)))
		redirec = 2;
	ret = ft_strdup((*find) + \
		(redirec + ft_strnlen((*find) + 1, ' ') + space));
	return (ret);//    cat < f1 | ls     |    ls -la    | wc -l >> f2
}*/

static char	*ft_inpfile(char **cmd)
{
	char	*find;
	char	*cleaned;
	char	*tmp;
	char	*ptr;
	int		step;

	find = ft_strnstr((*cmd), "<", ft_strlen((*cmd)));
	if (!find)
		find = ft_strnstr((*cmd), "<<", ft_strlen((*cmd)));
	if (find)
	{
		if ('<' == *(find + 1))
		{
			step = 3;
			find += step;
			tmp = ft_strndup(find, 2 + ft_strnlen(find + 1, ' '));
			cleaned = ft_strjoin("here_doc ", tmp);
		}
		else
		{
			step = 2;// ls < f1 || < f1 ls |
			find += step;
			cleaned = ft_strndup(find, 1 + ft_strnlen(find, ' '));
		}
		tmp = ft_strdup(find + 1 + ft_strnlen(find + 1, ' '));
		if ((*cmd[0]) != '<')
		{
			ptr = tmp;
			find = ft_strndup((*cmd), ft_strnlen((*cmd), ' '));
			tmp = ft_strjoin(find, ptr);
			free(ptr);
			free(find);
		}
		free((*cmd));
		(*cmd) = tmp;
		printf("cmdCHECK:+%s+\n", (*cmd));
		ft_putendl_fd("-----SYSTEM---------", 2);
		ft_putstr_fd("redirect part:(", 2);
		ft_putstr_fd(cleaned, 2);
		ft_putendl_fd(") from inpfile", 2);
		ft_putendl_fd("---------SY---------", 2);
		return (cleaned);
	}
	return (NULL);
}

static char	*ft_outfile(char **cmd)
{
	char	*find;
	char	*cleaned;
	char	*ptr;
	int		step;

	find = ft_strnstr((*cmd), ">", ft_strlen((*cmd)));
	step = 3;
	if (!find)
	{
		find = ft_strnstr((*cmd), ">>", ft_strlen((*cmd)));
		step = 4;
	}
	if (find)
	{
		find--;
		if (' ' == (*find + step))
			cleaned = ft_strndup(find, step + ft_strnlen(find + step, ' '));
		else
			cleaned = ft_strndup(find, step + ft_strlen(find + step));
		find = (*cmd);
		ptr = ft_strndup(find, ft_strnlen(find, '>'));
		ft_putendl_fd("-----SYSTEM---------", 2);
		ft_putstr_fd("redirect part:(", 2);
		ft_putstr_fd(cleaned, 2);
		ft_putendl_fd(") from outpfile", 2);
		ft_putendl_fd("---------SY---------", 2);
		free(find);
		(*cmd) = ptr;
		return (cleaned);
	}
	return (NULL);
}

static char	*ft_cleaner(char **cmd)
{
	char	*file;
	char	*end;
	char	*ptr;
	char	*tmp;

	if (!(*cmd))
		return (NULL);
	file = ft_inpfile(&(*cmd));
	end = ft_outfile(&(*cmd));
	tmp = ft_strjoin(file, (*cmd));
	ptr = tmp;
	tmp = ft_strjoin(ptr, end);//      cat << STOP      | ls -l -a | wc -l | cat >> f2
	tmp = ft_deldoublec(&tmp, ' ');
	free(ptr);
	free(end);
	free(file);
	free((*cmd));
	return (tmp);
}

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
		buildin = ft_iscinstr(src->cmds[i], '|');
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
			ft_pipex(src->argc, src->argv, src->export);
			printf("-------------PIPEX-------------\n");
		}
		ft_splfree(src->argv);
		i++;
	}
	free(src->str);
	src->str = NULL;
	ft_splfree(src->cmds);
}
