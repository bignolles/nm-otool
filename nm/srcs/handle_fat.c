/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 15:50:36 by marene            #+#    #+#             */
/*   Updated: 2016/09/09 12:12:36 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include <stdio.h>

#include "ft_nm.h"

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
			return ((fat_a.cputype == CPU_TYPE_X86) ? handle_32(file) : handle_64(file));
		}
		data += sizeof(struct fat_arch);
		++i;
	}
	return (NM_OK);
}
