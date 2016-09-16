/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 15:50:36 by marene            #+#    #+#             */
/*   Updated: 2016/09/16 13:02:18 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/*
static int		check_duplicate(t_symbol **symbols, t_symbol *newsym)
{
	int		i;
	i = 0;
	while (symbols[i])
	{
		if (ft_strequ(symbols[i]->name, newsym->name)
				&& symbols[i]->stab == newsym->stab
				&& symbols[i]->pext == newsym->pext
				&& symbols[i]->ext == newsym->ext
				&& symbols[i]->type == newsym->type
				&& symbols[i]->sectnb == newsym->sectnb
				&& symbols[i]->n_value == newsym->n_value
				&& symbols[i]->byte == newsym->byte)
			return (NM_NOK);
		++i;
	}
	return (NM_OK);
}
*/

static int		add_symbols(t_file *file, uint32_t nsyms,
		struct nlist_64 *symtable, void *strtable)
{
	uint32_t				i;
	uint32_t				j;
	int						offset;
	t_symbol				*newsym;

	offset = 0;
	//if (file->symbols == NULL)
		file->symbols = malloc(sizeof(t_symbol*) * (nsyms + 1));
//	else
//		file->symbols = t_symbol_array_realloc(file->symbols, nsyms, &offset);
	if (file->symbols != NULL)
	{
		i = 0;
		j = 0;
//		t_symbol_print_reinit(file->symbols);
		file->symbol_nb = nsyms;
		while (i < nsyms)
		{
			if (symtable[i].n_un.n_strx > 0)
			{
				newsym = t_symbol_construct_64(symtable[i], strtable);
			//	if (check_duplicate(file->symbols, newsym) == NM_OK)
				if (newsym != NULL)
				{
					file->symbols[j + offset] = newsym;
					++j;
				}
			}
			++i;
		}
		file->symbols[i] = NULL;
		return (NM_OK);
	}
	return (NM_NOK);
}

static void		fetch_sections(t_file *file, void *data,
		struct segment_command_64 *seg, uint32_t *sect_count)
{
	uint32_t					j;
	struct section_64			*sect;

	sect = data + sizeof(struct segment_command_64);
	j = 0;
	while (j < seg->nsects)
	{
		file->sections[(*sect_count)++] = t_section_construct_64(sect);
		sect++;
		++j;
	}
}

static int		add_section(t_file *file, uint32_t ncmds, uint32_t nsect,
		void *data)
{
	uint32_t					i;
	uint32_t					sect_count;
	struct load_command			*lc;

	if ((file->sections = malloc(sizeof(t_section*) * (nsect + 1))) != NULL)
	{
		i = 0;
		sect_count = 0;
		file->sections[nsect] = NULL;
		while (i < ncmds)
		{
			lc = (struct load_command*)data;
			if (lc->cmd == LC_SEGMENT_64)
			{
				fetch_sections(file, data,
						(struct segment_command_64 *)lc, &sect_count);
			}
			++i;
			data += lc->cmdsize;
		}
		return (NM_OK);
	}
	return (NM_NOK);
}

static void		handle_segment(t_file *file, void *data,
		struct load_command *lc, uint32_t *tot)
{
	struct segment_command_64	*seg;
	struct symtab_command		*sym;

	if (lc->cmd == LC_SYMTAB)
	{
		sym = (struct symtab_command*)data;
		add_symbols(file, sym->nsyms, file->content + sym->symoff,
				file->content + sym->stroff);
	}
	else if (lc->cmd == LC_SEGMENT_64)
	{
		seg = (struct segment_command_64*)data;
		*tot += seg->nsects;
	}
}

int				handle_64(t_file *file)
{
	struct mach_header_64		*header;
	struct load_command			*lc;
	uint32_t					i;
	void						*data;
	uint32_t					tot;

	tot = 0;
	data = file->content;
	header = (struct mach_header_64*)data;
	data += sizeof(struct mach_header_64);
	i = 0;
	while (i < header->ncmds)
	{
		lc = (struct load_command*)data;
		handle_segment(file, data, lc, &tot);
		data += lc->cmdsize;
		++i;
	}
	add_section(file, header->ncmds, tot, file->content +
			sizeof(struct mach_header_64));
	sort_symbols(file->symbols, symsort_ascii_addr);
	print_symbols(file->symbols, file->sections);
	return (NM_OK);
}
