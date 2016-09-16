/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/29 18:11:46 by marene            #+#    #+#             */
/*   Updated: 2016/09/15 14:32:13 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			symsort_ascii(t_symbol *s1, t_symbol *s2)
{
	int		ret;

	if (s1->name == NULL && s2->name == NULL)
		ret = 0;
	else if (s1->name == NULL && s2->name != NULL)
		ret = -1;
	else if (s1->name != NULL && s2->name == NULL)
		ret = 1;
	else
		ret = ft_strcmp(s1->name, s2->name);
	return (ret);
}

int			symsort_ascii_addr(t_symbol *s1, t_symbol *s2)
{
	int		ret;

	ret = symsort_ascii(s1, s2);
	if (ret == 0)
		ret = s1->n_value - s2->n_value;
	return (ret);
}
