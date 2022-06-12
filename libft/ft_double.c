/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:36:31 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/09 06:46:57 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_deldoublec(char **str, char c)
{
	char	*ret;
	char	*ptr;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ptr = (*str);
	printf("------------DELETEDOUBLE-----------\n");
	ret = (char *)malloc(sizeof(char) * (1 + ft_strlen((*str))));
	if (ret == NULL)
		return (NULL);
	while (ptr[i])
	{
		if (ptr[i + 1] == '\0' || !(ptr[i] == c && ptr[i] == ptr[i + 1]))
			ret[j++] = ptr[i];
		i++;
	}
	ret[j] = 0;
	free(ptr);
	tmp = ft_strdup(ret);
	free(ret);
	printf("after del double:+%s+\n", tmp);
	return (tmp);
}
