/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 11:50:32 by marene            #+#    #+#             */
/*   Updated: 2016/09/20 15:30:07 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

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

static void				print_objfile_name(t_file *file, struct ar_hdr *ar_h)
{
	ft_putstr(file->name);
	ft_putchar('(');
	ft_putstr((char*)(ar_h + 1));
	ft_putendl("):");
}

static void				browse_objfile(t_file *file)
{
	struct ar_hdr		*ar_h;
	uint32_t			magic_nb;
	void				*tmp;

	ar_h = file->content;
	tmp = file->content;
	ft_putchar('\n');
	print_objfile_name(file, ar_h);
	file->content += sizeof(*ar_h) + get_arheader_size(ar_h->ar_name);
	magic_nb = *(uint32_t*)file->content;
	if (magic_nb == MH_MAGIC)
		handle_32(file);
	else if (magic_nb == MH_MAGIC_64)
		handle_64(file);
	file->content = tmp;
}

int						handle_ar(t_file *file)
{
	struct ar_hdr			*ar_h;

	ar_h = (struct ar_hdr*)(file->content);
	while (file->content + ft_atoi(ar_h->ar_size) + sizeof(*ar_h)
			<= file->start + file->size)
	{
		if (file->symbols)
			t_symbol_destruct(&(file->symbols));
		browse_objfile(file);
		file->content += ft_atoi(ar_h->ar_size) + sizeof(*ar_h);
		ar_h = (struct ar_hdr*)(file->content);
	}
	return (NM_OK);
}
