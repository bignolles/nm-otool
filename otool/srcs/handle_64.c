/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 16:16:03 by marene            #+#    #+#             */
/*   Updated: 2016/09/20 14:11:59 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int				fetch_section(t_env *env, void *data,
		struct segment_command_64 *seg)
{
	struct section_64			*sec;
	uint32_t					j;

	sec = data + sizeof(struct segment_command_64);
	j = 0;
	while (j < seg->nsects)
	{
		if (ft_strequ(sec->segname, O_SEGTEXT)
				&& ft_strequ(sec->sectname, O_SECTEXT))
		{
			env->text = env->file + sec->offset;
			env->addr64 = sec->addr;
			env->addr32 = 0;
			env->size = sec->size;
			env->print64 = 1;
			return (OTOOL_OK);
		}
		++j;
		++sec;
	}
	return (OTOOL_NOK);
}

int						handle_64(t_env *env)
{
	struct mach_header_64		*header;
	struct load_command			*lc;
	void						*data;
	uint32_t					ncmds;
	uint32_t					i;

	header = (struct mach_header_64*)env->file;
	ncmds = header->ncmds;
	data = env->file + sizeof(*header);
	i = 0;
	while (i < ncmds)
	{
		lc = (struct load_command*)data;
		if (lc->cmd == LC_SEGMENT_64)
		{
			if (fetch_section(env, data,
						(struct segment_command_64*)lc) == OTOOL_OK)
				return (OTOOL_OK);
		}
		data += lc->cmdsize;
		++i;
	}
	ft_putendl("didn't find nothing boss");
	return (OTOOL_NOK);
}
