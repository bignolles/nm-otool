/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_reverse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/06 12:37:03 by marene            #+#    #+#             */
/*   Updated: 2016/09/20 15:29:19 by marene           ###   ########.fr       */
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
