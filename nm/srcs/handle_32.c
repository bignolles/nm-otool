/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 15:50:36 by marene            #+#    #+#             */
/*   Updated: 2016/09/01 12:57:17 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
#include "ft_nm.h"

extern t_env	g_foo;

static int		add_symbols(t_file *file, uint32_t nsyms, struct nlist *symtable, void *strtable)
{
	uint32_t				i;
	uint32_t				j;

	if ((file->symbols = malloc(sizeof(t_symbol*) * (nsyms + 1))) != NULL)
	{
		i = 0;
		j = 0;
		file->symbol_nb = nsyms;
		while (i < nsyms)
		{
			if (symtable[i].n_un.n_strx > 0)
			{
				file->symbols[j] = t_symbol_construct_32(symtable[i], strtable);
				++j;
			}
			++i;
		}
		file->symbols[i] = NULL;
		return (NM_OK);
	}
	return (NM_NOK);
}

static int		add_section(t_file *file, uint32_t ncmds, uint32_t nsect, void *data)
{
	uint32_t					i;
	uint32_t					j;
	uint32_t					sect_count;;
	struct load_command			*lc;
	struct segment_command		*seg;
	struct section				*sect;

	if ((file->sections = malloc(sizeof(t_section*) * (nsect + 1))) != NULL)
	{
		i = 0;
		sect_count = 0;
		file->sections[nsect] = NULL;
		while (i < ncmds)
		{
			lc = (struct load_command*)data;
			if (lc->cmd == LC_SEGMENT)
			{
				seg = (struct segment_command*)data;
				sect = data + sizeof(struct segment_command);
				j = 0;
				while (j < seg->nsects)
				{
					file->sections[sect_count++] = t_section_construct_32(sect);
					sect++;
					++j;
				}
			}
			++i;
			data += lc->cmdsize;
		}
		return (NM_OK);
	}
	return (NM_NOK);
}

static void		foo_print_symtype(t_symbol *symbol, t_section **sections)
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

static void		foo_printsymbols(t_symbol **symbols, t_section **sections)
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
				ft_putstr("        ");
				ft_putstr(" ");
			}
			else
			{
				putaddr32(symbols[i]->n_value, 1);
				ft_putstr(" ");
			}
			foo_print_symtype(symbols[i], sections);
			ft_putstr((symbols[i]->name) ? symbols[i]->name : "NULL");
			ft_putchar('\n');
		}
		++i;
	}
}

int				handle_32(t_file *file)
{
	struct mach_header			header;
	struct load_command			lc;
	struct symtab_command		*sym;
	uint32_t					ncmds;
	uint32_t					i;
	void						*data;
	struct segment_command		*seg;
	uint32_t					tot;

	tot = 0;
	data = file->content;
	header = *(struct mach_header*)data;
	ncmds = header.ncmds;
	data += sizeof(struct mach_header);
	i = 0;
	while (i < ncmds)
	{
		lc = *(struct load_command*)data;
		if (lc.cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command*)data;
			add_symbols(file, sym->nsyms, file->content + sym->symoff, file->content + sym->stroff);
		}
		else if (lc.cmd == LC_SEGMENT)
		{
			seg = (struct segment_command*)data;
			tot += seg->nsects;
		}
		else if (lc.cmd == LC_SEGMENT_64)
			printf("64b, WTF?\n");
		data += lc.cmdsize;
		++i;
	}
	add_section(file, ncmds, tot, file->content + sizeof(struct mach_header));
	sort_symbols(file->symbols, symsort_ascii);
	foo_printsymbols(file->symbols, file->sections);
	return (NM_OK);
}
