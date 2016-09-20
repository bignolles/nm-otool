/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 16:09:35 by marene            #+#    #+#             */
/*   Updated: 2016/09/20 15:24:51 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

t_handler				get_handler(t_env *env)
{
	uint32_t			magic;
	void				*data;
	struct ar_hdr		ar_h;

	magic = *(uint32_t*)env->file;
	if (magic == MH_MAGIC)
		return (handle_32);
	else if (magic == MH_MAGIC_64)
		return (handle_64);
	else if (magic == FAT_CIGAM)
		return (handle_fat);
	else if (ft_strncmp(env->file, ARMAG, SARMAG) == 0)
	{
		ar_h = *(struct ar_hdr*)(env->file + SARMAG);
		data = env->file + SARMAG + sizeof(struct ar_hdr)
			+ ft_atoi(ar_h.ar_size);
		env->file = data;
		return (handle_ar);
	}
	else
		return (NULL);
}
