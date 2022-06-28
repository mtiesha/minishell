/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:02:34 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/28 17:53:20 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_left_right_part(char *cmd, char *find, char *tmp)
{
	int		step;
	char	c;
	char	*left;
	char	*right;
	char	*ret;

	step = 2;
	c = *find;
	if ('<' == *(find + 1) || '>' == *(find + 1))
		step = 3;
	left = ft_strndup(cmd, ft_strnlen(cmd, c));
	find += step + ft_strnlen(find + step, ' ');
	right = ft_strdup(find);
	if (ft_iscinstr(left, '|'))
	{
		tmp = left;
		left = ft_strdup(left + 1);
		free(tmp);
	}
	ret = ft_strjoin(left, right);
	ft_multifree(left, right, NULL);
	return (ret);
}

static void	ft_cust_file(char *cmd, char **cmd_p, char **inp_p, int npipe)
{
	char	*find;
	char	*tmp;

	tmp = NULL;
	find = ft_strnstr(cmd, "<", ft_strlen(cmd));
	if (!find)
		find = ft_strnstr(cmd, "<<", ft_strlen(cmd));
	(*cmd_p) = ft_left_right_part(cmd, find, tmp);
	if ('<' == *(find + 1))
	{
		find += 3;
		tmp = ft_strndup(find, ft_strnlen(find, ' '));
		(*inp_p) = ft_strjoin("here_doc ", tmp);
		free(tmp);
	}
	else
	{
		if (0 == npipe)
			find += 2;
		else
			npipe = 2;
		(*inp_p) = ft_strndup(find, npipe + ft_strnlen(find + npipe, ' '));
		if (npipe)
		{
			tmp = (*inp_p);
			(*inp_p) = ft_strjoin("| ", (*inp_p));
			free(tmp);
		}
	}
}

char	*ft_inpfile(char **cmd, int npipe)
{
	char	*find;
	char	*inp_part;
	char	*cmd_part;

	find = ft_strnstr((*cmd), "<", ft_strnlen((*cmd) + 1, '|'));
	if (!find)
		find = ft_strnstr((*cmd), "<<", ft_strnlen((*cmd) + 1, '|'));
	if (find)
	{
		ft_cust_file((*cmd), &cmd_part, &inp_part, npipe);
		free((*cmd));
		(*cmd) = cmd_part;
		return (inp_part);
	}
	return (NULL);
}

char	*ft_outfile(char **cmd, int dop_variable)
{
	char	*find;
	char	*out_part;
	char	*cmd_part;
	char	*tmp;

	tmp = NULL;
	find = NULL;
	find = ft_strrnstr((*cmd), ">> ", ft_strrnlen((*cmd), '|'));
	if (!find)
	{
		find = ft_strrnstr((*cmd), "> ", ft_strrnlen((*cmd), '|'));
		dop_variable = 0;
	}
	if (find)
	{
		out_part = ft_strndup(find, 2 + dop_variable + \
			ft_strnlen(find + 2 + dop_variable, ' '));
		cmd_part = ft_left_right_part((*cmd), find, tmp);
		free((*cmd));
		(*cmd) = cmd_part;
		return (out_part);
	}
	return (NULL);
}
