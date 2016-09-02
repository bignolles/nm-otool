/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/02 14:38:33 by marene            #+#    #+#             */
/*   Updated: 2016/09/02 14:39:38 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		print_symtype(t_symbol *symbol, t_section **sections)
{
	char		type;

	if (symbol->type == N_UNDF)
		type = 'u';
	else if (symbol->type == N_ABS)
		type = 'a';
	else if (symbol->type == N_SECT)
		type = sections[symbol->sectnb]->secsym;
	else if (symbol->type == N_INDR)
		type = 'i';
	if (symbol->ext)
		type = type + 'A' - 'a';
	if (symbol->stab)
		type = '-';
	ft_putchar(type);
	ft_putchar(' ');
}

void			print_symbols(t_symbol **symbols, t_section **sections)
{
	int		i;

	i = 0;
	(void)sections;
	while (symbols[i] != NULL)
	{
		if (symbols[i]->name != NULL && !symbols[i]->stab)
		{
			if (symbols[i]->type == N_UNDF)
			{
				ft_putstr("                ");
				ft_putstr(" ");
			}
			else
			{
				putaddr64(symbols[i]->n_value, 1);
				ft_putstr(" ");
			}
			print_symtype(symbols[i], sections);
			ft_putstr((symbols[i]->name) ? symbols[i]->name : "NULL");
			ft_putchar('\n');
		}
		++i;
	}
}
