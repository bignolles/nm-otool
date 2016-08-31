/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 14:48:00 by marene            #+#    #+#             */
/*   Updated: 2016/08/30 16:29:53 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*copy;

	i = 0;
	copy = NULL;
	if (s1 != NULL)
	{
		len = ft_strlen(s1) + 1;
		copy = malloc(len * sizeof(char));
		while (i < len)
		{
			copy[i] = s1[i];
			i++;
		}
	}
	return (copy);
}
