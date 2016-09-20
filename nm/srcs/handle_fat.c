/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 15:50:36 by marene            #+#    #+#             */
/*   Updated: 2016/09/20 15:30:30 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int		call_handle(t_file *file)
{
	unsigned int		magic_nb;
	void				*data;
	struct ar_hdr		ar_h;

	magic_nb = *(unsigned int*)(file->content);
	if (magic_nb == MH_MAGIC)
		return (handle_32(file));
	else if (magic_nb == MH_MAGIC_64)
		return (handle_64(file));
	else if (ft_strncmp(file->content, ARMAG, SARMAG) == 0)
	{
		ar_h = *(struct ar_hdr*)(file->content + SARMAG);
		data = file->content + SARMAG + sizeof(struct ar_hdr);
		data += ft_atoi(ar_h.ar_size);
		file->content = data;
		return (handle_ar(file));
	}
	return (NM_NOK);
}

int				handle_fat(t_file *file)
{
	uint32_t					i;
	void						*data;
	struct fat_header			fat_h;
	struct fat_arch				fat_a;

	data = file->content;
	fat_h = reverse_fat_header(data);
	data += sizeof(struct fat_header);
	i = 0;
	while (i < fat_h.nfat_arch)
	{
		fat_a = reverse_fat_arch(data);
		if (fat_a.cputype == CPU_TYPE_X86_64)
		{
			file->content += fat_a.offset;
			return (call_handle(file));
		}
		data += sizeof(struct fat_arch);
		++i;
	}
	return (NM_OK);
}
