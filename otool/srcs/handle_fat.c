/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 15:50:36 by marene            #+#    #+#             */
/*   Updated: 2016/09/20 15:27:36 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int		call_handle(t_env *env)
{
	unsigned int		magic_nb;
	void				*data;
	struct ar_hdr		ar_h;

	magic_nb = *(unsigned int*)(env->file);
	if (magic_nb == MH_MAGIC)
		return (handle_32(env));
	else if (magic_nb == MH_MAGIC_64)
		return (handle_64(env));
	else if (ft_strncmp(env->file, ARMAG, SARMAG) == 0)
	{
		ar_h = *(struct ar_hdr*)(env->file + SARMAG);
		data = env->file + SARMAG + sizeof(struct ar_hdr);
		data += ft_atoi(ar_h.ar_size);
		env->file = data;
		return (handle_ar(env));
	}
	return (OTOOL_NOK);
}

int				handle_fat(t_env *env)
{
	uint32_t					i;
	void						*data;
	struct fat_header			fat_h;
	struct fat_arch				fat_a;

	data = env->file;
	fat_h = reverse_fat_header(data);
	data += sizeof(struct fat_header);
	i = 0;
	while (i < fat_h.nfat_arch)
	{
		fat_a = reverse_fat_arch(data);
		if (fat_a.cputype == CPU_TYPE_X86_64)
		{
			env->file += fat_a.offset;
			return (call_handle(env));
		}
		data += sizeof(struct fat_arch);
		++i;
	}
	return (OTOOL_OK);
}
