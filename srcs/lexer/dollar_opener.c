/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_opener.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:56:01 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/29 06:36:50 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_source(t_src *s, char **end, char **start, size_t i)
{
	char	*val;
	int		shift;

	val = NULL;
	val = ft_get_strnspl(s->envp, s->str + i + 1, '=');
	if (!val)
		shift = 1 + ft_strnlen(s->str + i, ' ');
	else
		shift = 1 + ft_strnlen(val, '=');
	(*start) = ft_strndup(s->str, i);
	if ((int)(i + shift) > (int)(ft_strlen(s->str) \
		- (1 + ft_strnlen(s->str, ' '))))
		(*end) = NULL;
	else
		(*end) = ft_strndup(s->str + i + shift, \
	ft_strlen(s->str + i + shift));
	free(s->str);
	if (val)
		val += shift;
	s->str = ft_strjoin((*start), val);
}

static int	ft_replase_dollar_var(t_src *s, int quot, size_t i)
{
	char	*start;
	char	*end;

	while (i <= ft_strlen(s->str) && s->str[i])
	{
		if (i != 0 && '$' == s->str[i] && !quot \
			&& s->str[i + 1] && ft_isalpha(s->str[i + 1]))
		{
			ft_source(s, &end, &start, i);
			ft_multifree(start, NULL, NULL);
			start = s->str;
			s->str = ft_strjoin(s->str, end);
			ft_multifree(start, end, NULL);
		}
		i++;
	}
	return (1);
}

static void	ft_seek_and_destroy(int i, t_src *s, int quot)
{
	char	*ret_val;
	int		k;

	k = 0;
	if (s->str[i + 1] && '$' == s->str[i + 1])
	{
		s->str = ft_chardel(&s->str, i);
		s->str = ft_chardel(&s->str, i);
	}
	else if (s->str[i + 1] && '?' == s->str[i + 1])
	{
		s->str = ft_chardel(&s->str, i);
		s->str = ft_chardel(&s->str, i);
		if (s->ret > 127)
			s->ret = s->ret >> 8 & 0x000000ff;
		ret_val = ft_itoa(s->ret);
		while (ret_val[k])
			s->str = ft_charadd(&s->str, i++, ret_val[k++]);
		free(ret_val);
	}
	else
		ft_replase_dollar_var(s, quot, 0);
}

static int	ft_dollar_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ('$' == str[i] && str[i + 1] && str[i + 2] \
			&&'$' == str[i + 1] && '$' == str[i + 2])
		{
			ft_putendl_fd("lexer error [dollar syntax]", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

char	*ft_dollar_opener(t_src *s)
{
	int		i;
	int		quot;
	char	*str;

	i = 0;
	quot = 0;
	str = ft_strdup(s->str);
	if (!ft_dollar_syntax(str))
	{
		ft_multifree(str, s->str, NULL);
		s->ret = 127;
		return (NULL);
	}
	while (i < (int)(ft_strlen(s->str)))
	{
		if ('\'' == s->str[i] && 0 == quot && ft_iscinstr(s->str + i + 1, '\''))
			quot = 1;
		else if ('\'' == s->str[i] && 1 == quot)
			quot = 0;
		if ('$' == s->str[i])
			ft_seek_and_destroy(i, s, quot);
		i++;
	}
	free(str);
	return (s->str);
}
