/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:33:08 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/27 16:51:47 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_ressurection_spl(char **set_pipes)
{
	int		i;
	char	*tmp;
	char	*ret;
	char	*ptr;

	i = 0;
	ft_putendl_fd("PROVEROCHKA----+++++_---------", 2);
	ft_putspl_fd(set_pipes, 2);
	ft_putendl_fd("PROVEROCHKA----+++++_---------", 2);
	ret = ft_strdup(set_pipes[i]);
	i++;
	while (set_pipes[i])
	{
		tmp = ret;
		if ('|' != set_pipes[i][0])
		{
			ptr = ft_strjoin(tmp, " | ");
			ret = ft_strjoin(ptr, set_pipes[i]);
			free(ptr);
		}
		else
			ret = ft_strjoinchar(ret, set_pipes[i], ' ');
		free(tmp);
		i++;
	}
	printf("POSLE RESURRECTION SPL IN CLEANER: %s\n", ret);
	return (ret);
}

static char	**ft_cleaner_logic(char **start, char **end, char **tmp, char **cmd)
{
	char	**set_pipes;
	int		i;
	char	*ptr;

	(*cmd) = ft_deldoublec(&(*cmd), ' ');
	printf("CMD:%s\n", (*cmd));
	if (ft_strncmp((*cmd), "echo ", 5))
	{
		set_pipes = ft_split((*cmd), '|');

	}
	else
		set_pipes = ft_split((*cmd), 0);
	if (!set_pipes)
		return (NULL);
	i = 0;
	ft_putendl_fd("SETPIPES cl logic+:", 2);
	ft_putspl_fd(set_pipes, 2);
	ft_putendl_fd("SETPIPES+\n", 2);
	while (set_pipes[i])
	{
		printf("I into Cleaner: %d\n", i);
		(*tmp) = set_pipes[i];
		if (0 == i)
			set_pipes[i] = ft_strjoin(" ", set_pipes[i]);
		else
			set_pipes[i] = ft_strjoin("| ", set_pipes[i]);
		free(*tmp);
		(*start) = ft_inpfile(&set_pipes[i], i);
		printf("1! after INFILE: +%s+\n", (*start));
		(*end) = ft_outfile(&set_pipes[i], 1);
		printf("2! after OUTFILE: +%s+\n", (*end));
		(*tmp) = ft_strjoin((*start), set_pipes[i]);
		ptr = (*tmp);
		(*tmp) = ft_strjoin(ptr, (*end));
		free(ptr);
		ptr = set_pipes[i];
		set_pipes[i] = (*tmp);
		ft_multifree(ptr, (*start), (*end));
		i++;
	}
	printf("3! DONE array: \n");
	ft_putspl_fd(set_pipes, 2);
	ft_putendl_fd("=======end logic=======", 2);
	// ft_putendl_fd((*cmd), 2);
	return (set_pipes);
}

char	*ft_cleaner(char **cmd)
{
	char	*file;
	char	*end;
	char	*tmp;
	char	**set_pipes;

	if (!(*cmd))
		return (NULL);
	if (ft_strnstr((*cmd), "echo ", 5))
		return ((*cmd));
	(*cmd) = ft_deldoublec(&(*cmd), ' ');
	printf("cleaner] =====+++PIPE ZONE+++======\n");
	set_pipes = ft_cleaner_logic(&file, &end, &tmp, &(*cmd));
	if (!set_pipes)
		return (NULL);
	tmp = ft_ressurection_spl(set_pipes);
	ft_splfree(set_pipes);
	if (!ft_strnstr(tmp, "echo ", 5))
		tmp = ft_deldoublec(&tmp, ' ');
	ft_multifree((*cmd), NULL, NULL);
	printf("end cleaner] =====+++PIPE ZONE+++======\n");
	return (tmp);
}
