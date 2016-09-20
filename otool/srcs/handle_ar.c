/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 11:50:32 by marene            #+#    #+#             */
/*   Updated: 2016/09/20 15:26:13 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

/*
** file->content starts at the 2nd ar_hdr described in the archive
** (Cf srcs/get_magic.c)
*/

static int				get_arheader_size(char *ar_name)
{
	char		*str_size;

	str_size = ft_strstr(ar_name, "/");
	return ((str_size != NULL) ? ft_atoi(str_size + 1) : -1);
}

static void				print_objfile_name(t_env *env, struct ar_hdr *ar_h)
{
	ft_putstr(env->filename);
	ft_putchar('(');
	ft_putstr((char*)(ar_h + 1));
	ft_putendl("):");
}

static void				browse_objfile(t_env *env)
{
	struct ar_hdr		*ar_h;
	uint32_t			magic_nb;
	void				*tmp;

	ar_h = env->file;
	tmp = env->file;
	print_objfile_name(env, ar_h);
	env->file += sizeof(*ar_h) + get_arheader_size(ar_h->ar_name);
	magic_nb = *(uint32_t*)env->file;
	if (magic_nb == MH_MAGIC)
	{
		handle_32(env);
	}
	else if (magic_nb == MH_MAGIC_64)
	{
		handle_64(env);
	}
	else
	{
		ft_putendl("nop!");
	}
	print_text(env);
	env->file = tmp;
}

int						handle_ar(t_env *env)
{
	struct ar_hdr			*ar_h;

	ft_putstr("Archive : ");
	ft_putendl(env->filename);
	ar_h = (struct ar_hdr*)(env->file);
	while (env->file + ft_atoi(ar_h->ar_size) + sizeof(*ar_h)
			<= env->start + env->filesize)
	{
		browse_objfile(env);
		env->file += ft_atoi(ar_h->ar_size) + sizeof(*ar_h);
		ar_h = (struct ar_hdr*)(env->file);
	}
	env->text = NULL;
	return (OTOOL_OK);
}
