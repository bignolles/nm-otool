/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_magic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 14:52:49 by marene            #+#    #+#             */
/*   Updated: 2016/09/14 15:36:27 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int				get_magic(t_env *env)
{
	unsigned int		magic_nb;
	void				*data = env->froot->content;
	struct ar_hdr		ar_h;
	//int					off;
	//void				*tmp;
//	struct ranlib		ranl;

	magic_nb = *(int *)env->froot->content;
	if (magic_nb == MH_MAGIC)
	{
		env->handler = handle_32;
	}
	else if (magic_nb == MH_MAGIC_64)
	{
		env->handler = handle_64;
	}
	else if (magic_nb == FAT_CIGAM)
	{
		env->handler = handle_fat;
	}
	else if (ft_strncmp(env->froot->content, ARMAG, SARMAG) == 0)
	{
		ar_h = *(struct ar_hdr*)(env->froot->content + SARMAG);
		data = env->froot->content + SARMAG + sizeof(struct ar_hdr);
		data += ft_atoi(ar_h.ar_size);
		/*
		ar_h = *(struct ar_hdr*)(data);
		off = get_size(ar_h.ar_name);
		tmp = (data + sizeof(ar_h) + off);
		if (*(unsigned int*)(tmp) == MH_MAGIC_64)
			printf("IT FUCKING WORKED!\n");
			*/
		env->froot->content = data;
		env->handler = handle_ar;
	}
	else
	{
		env->handler = NULL;
		return (NM_NOK);
	}
	return (NM_OK);
}
