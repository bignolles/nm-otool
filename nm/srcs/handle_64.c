/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 15:50:36 by marene            #+#    #+#             */
/*   Updated: 2016/08/24 16:56:14 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
#include "ft_nm.h"

static void		print_output(uint32_t nsyms, struct nlist_64 *symtable, void *strtable)
{
	uint32_t			i;
	uint32_t			nstab;
	uint32_t			npext;
	uint32_t			ntype;
	uint32_t			next;

	i = 0;
	while (i < nsyms)
	{
		if (/*((symtable[i].n_type & N_STAB) == 0) && (symtable[i].n_type & N_TYPE) == N_SECT
				&&*/ symtable[i].n_un.n_strx > 1)
		{
			nstab = (symtable[i].n_type & N_STAB);
			npext = (symtable[i].n_type & N_PEXT);
			ntype = (symtable[i].n_type & N_TYPE);
			next = (symtable[i].n_type & N_EXT);
			printf("%s\n\tn_type %u {N_STAB %u, N_PEXT %u, N_TYPE %u, N_EXT %u}\n\tn_sect = %u\n", strtable + symtable[i].n_un.n_strx, symtable[i].n_type, nstab, npext, ntype, next, symtable[i].n_sect);
//			printf("%s\n", strtable + symtable[i].n_un.n_strx);
		}
		else if (symtable[i].n_un.n_strx <= 1 && ft_strlen(strtable + symtable[i].n_un.n_strx) != 0)
		{
			printf("ERROR : %u : %s\n", symtable[i].n_un.n_strx, strtable + symtable[i].n_un.n_strx);
		}
		//printf("%u < %u\n", i, nsyms);
		++i;
	}

}

int				handle_64(t_file *file)
{
	struct mach_header_64		header;
	struct load_command			lc;
	struct symtab_command		*sym;
	uint32_t					ncmds;
	uint32_t					i;
	void						*data;

	struct segment_command_64	*seg;
	struct section_64			*sect;
	uint32_t					nsect;
	uint32_t					j;
	uint32_t					tot;

	tot = 1;
	data = file->content;
	header = *(struct mach_header_64*)data;
	ncmds = header.ncmds;
	data += sizeof(struct mach_header_64);
	printf("ncmds : %u\n", ncmds);
	i = 0;
	while (i < ncmds)
	{
		lc = *(struct load_command*)data;
		if (lc.cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command*)data;
			print_output(sym->nsyms, file->content + sym->symoff, file->content + sym->stroff);
			break;
		}
		else if (lc.cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64*)data;
			//printf("\tsizeof(struct segment_command) = %lu\n", sizeof(struct segment_command));
			//printf("seg->fileoff = %llu\n", seg->fileoff);
			nsect = seg->nsects;
			sect = data + sizeof(struct segment_command_64);
			j = 0;
		//	printf("\tseg size : %u. sizeof(seg_command) : %lu. sizeof(section_64) : %lu\n", lc.cmdsize, sizeof(struct segment_command), sizeof(struct section_64));
			printf("segment %u : %s (%u sections)\n", i, seg->segname, seg->nsects);
			while (j < nsect)
			{
				printf("\t[%u] %s (%s) (size : %llu)\n", tot, sect->sectname, sect->segname, sect->size);
				sect++;
				++j;
				++tot;
			}
		}
		else if (lc.cmd == LC_SEGMENT)
			printf("32b, WTF?\n");
		else
			printf("IDK WHAT THIS IS\n");
		data += lc.cmdsize;
		++i;
	}
	return (NM_OK);
}
