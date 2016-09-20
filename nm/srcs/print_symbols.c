/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/02 14:38:33 by marene            #+#    #+#             */
/*   Updated: 2016/09/20 10:12:01 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

const int		g_foo;

static void		print_symtype(t_symbol *symbol, t_section **sections)
{
	char		type;

	if (symbol->type == N_UNDF)
		type = (symbol->n_value == 0) ? 'u' : 'c';
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

static void		print_addr(t_symbol *sym)
{
	static char		blank64[] = "                ";
	static char		blank32[] = "        ";

	if (sym->type == N_UNDF && sym->n_value == 0)
	{
		if (sym->byte == NM_SYM64)
			ft_putstr(blank64);
		else if (sym->byte == NM_SYM32)
			ft_putstr(blank32);
	}
	else
	{
		if (sym->byte == NM_SYM64)
			putaddr64(sym->n_value, 1);
		else if (sym->byte == NM_SYM32)
			putaddr32(sym->n_value, 1);
	}
	ft_putchar(' ');
}

void			print_symbols(t_symbol **symbols, t_section **sections)
{
	int		i;
	i = 0;
	while (symbols && symbols[i] != NULL)
	{
		if (symbols[i]->name != NULL && !symbols[i]->stab)
		{
			print_addr(symbols[i]);
			print_symtype(symbols[i], sections);
			ft_putstr((symbols[i]->name) ? symbols[i]->name : "NULL");
			ft_putchar('\n');
		}
		++i;
	}
}
