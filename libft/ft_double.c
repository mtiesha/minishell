/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:36:31 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/13 11:51:16 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	return (tmp);
}
