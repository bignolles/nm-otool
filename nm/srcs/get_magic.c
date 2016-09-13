/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_magic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 14:52:49 by marene            #+#    #+#             */
/*   Updated: 2016/09/13 16:56:29 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <mach-o/ranlib.h>

#include "ft_nm.h"

static int		get_size(char *ar_name)
{
	return (ft_atoi(ft_strstr(ar_name, "/") + 1));
}

int				get_magic(t_env *env)
{
	unsigned int		magic_nb;
	void				*data = env->froot->content;
	void				*tmp;
	struct ar_hdr		ar_h;
	int					off;
//	struct ranlib		ranl;

	magic_nb = *(int *)env->froot->content;
	if (magic_nb == MH_MAGIC)
	{
		printf("magic_32\n");
		env->handler = handle_32;
	}
	else if (magic_nb == MH_MAGIC_64)
	{
		printf("magic_64\n");
		env->handler = handle_64;
	}
	else if (magic_nb == FAT_CIGAM)
	{
		printf("magic_fat\n");
		env->handler = handle_fat;
	}
	else if (ft_strncmp(env->froot->content, ARMAG, SARMAG) == 0)
	{
		printf("magic_lib\n");
		ar_h = *(struct ar_hdr*)(env->froot->content + SARMAG);
		data = env->froot->content + SARMAG + sizeof(struct ar_hdr);
		data += ft_atoi(ar_h.ar_size);
		ar_h = *(struct ar_hdr*)(data);
		off = get_size(ar_h.ar_name);
		tmp = (data + sizeof(ar_h) + off);
		if (*(unsigned int*)(tmp) == MH_MAGIC_64)
			printf("IT FUCKING WORKED!\n");
		env->froot->content = tmp;
		return (get_magic(env));
		return (NM_NOK);
	}
	else
	{
		printf("magic_squatShit\n");
		env->handler = NULL;
		return (NM_NOK);
	}
	return (NM_OK);
}
