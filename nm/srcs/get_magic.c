/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_magic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 14:52:49 by marene            #+#    #+#             */
/*   Updated: 2016/09/13 14:20:50 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <mach-o/ranlib.h>

#include "ft_nm.h"

static int		get_ar_size(char *ar_name)
{
	char	*str_size;

	str_size = ft_strstr(ar_name, "/");
	return ((str_size != NULL) ? ft_atoi(str_size + 1) : -1);
}

int				get_magic(t_env *env)
{
	unsigned int		magic_nb;
	void				*data = env->froot->content;
	struct ar_hdr		ar_h;
	int					ar_size;
	int					obj_file_nb;
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
		ar_size = get_ar_size(ar_h.ar_name);
		obj_file_nb = *(int*)(data + ar_size);
		printf("ar_h.ar_name : [%s]\nobj_file_nb : %lu\n", ar_h.ar_name, obj_file_nb / sizeof(struct ranlib));
		printf("ar_size : [%s] (%lx)\n", ar_h.ar_size, (data + ft_atoi(ar_h.ar_size)) - env->froot->content);
		ar_h = *(struct ar_hdr*)(data + ft_atoi(ar_h.ar_size));
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
