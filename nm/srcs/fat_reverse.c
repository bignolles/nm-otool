/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_reverse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 12:37:03 by marene            #+#    #+#             */
/*   Updated: 2016/09/07 16:22:58 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

struct fat_header		reverse_fat_header(struct fat_header *fat_h)
{
	struct fat_header	ret;
	
	ret = *fat_h;
	ret.magic = ft_swap32(fat_h->magic);
	ret.nfat_arch = ft_swap32(fat_h->nfat_arch);
	if (ret.magic != FAT_MAGIC)
	{
		ft_putendl("fatal error : fat_header invalid magic number");
		exit(1);
	}
	return (ret);
}

struct fat_arch			reverse_fat_arch(struct fat_arch *f)
{
	struct fat_arch		ret;

	ret.cputype = ft_swap32(f->cputype);
	ret.cpusubtype = ft_swap32(f->cpusubtype);
	ret.offset = ft_swap32(f->offset);
	ret.size = ft_swap32(f->size);
	ret.align = ft_swap32(f->align);
	return (ret);
}

struct mach_header		reverse_mach_header(struct mach_header *h)
{
	struct mach_header		ret;

	ret.magic = ft_swap32(h->magic);
	ret.cputype = ft_swap32(h->cputype);
	ret.cpusubtype = ft_swap32(h->cpusubtype);
	ret.filetype = ft_swap32(h->filetype);
	ret.ncmds = ft_swap32(h->ncmds);
	ret.sizeofcmds = ft_swap32(h->sizeofcmds);
	ret.flags = ft_swap32(h->flags);
	if (ret.magic != MH_MAGIC && ret.magic != MH_CIGAM)
	{
		ft_putendl("fatal error : mach_header invalid magic number");
		exit(1);
	}
	return (ret);
}

struct load_command		reverse_load_command(struct load_command *l)
{
	struct load_command			ret;

	ret.cmd = ft_swap32(l->cmd);
	ret.cmdsize = ft_swap32(l->cmdsize);
	return (ret);
}

struct symtab_command	reverse_symtab_command(struct symtab_command *s)
{
	struct symtab_command		ret;

	ret.cmd = ft_swap32(s->cmd);
	ret.cmdsize = ft_swap32(s->cmdsize);
	ret.symoff = ft_swap32(s->symoff);
	ret.nsyms = ft_swap32(s->nsyms);
	ret.stroff = ft_swap32(s->stroff);
	ret.strsize = ft_swap32(s->strsize);
	return (ret);
}

struct segment_command	reverse_segment_command(struct segment_command *s)
{
	struct segment_command		ret;

	ret.cmd = ft_swap32(s->cmd);
	ret.cmdsize = ft_swap32(s->cmdsize);
	ft_memcpy(ret.segname, s->segname, 16);
	ret.vmaddr = ft_swap32(s->vmaddr);
	ret.vmsize = ft_swap32(s->vmsize);
	ret.fileoff = ft_swap32(s->fileoff);
	ret.filesize = ft_swap32(s->filesize);
	ret.maxprot = ft_swap32(s->maxprot);
	ret.initprot = ft_swap32(s->initprot);
	ret.nsects = ft_swap32(s->nsects);
	ret.flags = ft_swap32(s->flags);
	return (ret);
}

struct nlist			reverse_nlist(struct nlist *n)
{
	struct nlist	ret;

	ret.n_un.n_strx = ft_swap32(n->n_un.n_strx);
	ret.n_type = n->n_type;
	ret.n_sect = n->n_sect;
	ret.n_desc = ft_swap16(n->n_desc);
	ret.n_value = ft_swap32(n->n_value);
	return (ret);
}

struct section			reverse_section(struct section *s)
{
	struct section		ret;

	ft_memcpy(ret.sectname, s->sectname, 16);
	ft_memcpy(ret.segname, s->segname, 16);
	ret.addr = ft_swap32(s->addr);
	ret.size = ft_swap32(s->size);
	ret.offset = ft_swap32(s->offset);
	ret.align = ft_swap32(s->align);
	ret.reloff = ft_swap32(s->reloff);
	ret.nreloc = ft_swap32(s->nreloc);
	ret.flags = ft_swap32(s->flags);
	ret.reserved1 = ft_swap32(s->reserved1);
	ret.reserved2 = ft_swap32(s->reserved2);
	return (ret);
}
