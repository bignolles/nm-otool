/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symsort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/29 15:20:39 by marene            #+#    #+#             */
/*   Updated: 2016/09/07 15:41:06 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int					sort_symbols(t_symbol **symbols, t_symsort sort)
{
	t_symbol	*tmp;
	uint32_t	i;
	uint32_t	j;
	uint32_t	min_ptr;

	i = 0;
	while (symbols && symbols[i])
	{
		j = i;
		min_ptr = j;
		while (symbols[j])
		{
			if (min_ptr != j && sort(symbols[min_ptr], symbols[j]) > 0)
				min_ptr = j;
			++j;
		}
		if (i != min_ptr)
		{
			tmp = symbols[i];
			symbols[i] = symbols[min_ptr];
			symbols[min_ptr] = tmp;
		}
		++i;
	}
	return (NM_OK);
}
