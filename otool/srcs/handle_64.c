/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 16:16:03 by marene            #+#    #+#             */
/*   Updated: 2016/09/01 18:34:30 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void					*handle_64(void *file)
{
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct segment_command_64	*seg;
	struct section_64			*sec;
	void						*data;
	uint32_t					ncmds;
	uint32_t					i;
	uint32_t					j;

	header = (struct mach_header_64*)file;
	ncmds = header->ncmds;
	data = file + sizeof(*header);
	i = 0;
	while (i < ncmds)
	{
		lc = (struct load_command*)data;
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64*)lc;
			sec = data + sizeof(struct segment_command_64);
			j = 0;
			while (j < seg->nsects)
			{
				if (ft_strequ(sec->segname, O_SEGTEXT) && ft_strequ(sec->sectname, O_SECTEXT))
				{
					ft_putendl("found __TEXT, __text");
					return (file + sec->offset);
				}
				++j;
				++sec;
			}
		}
		data += lc->cmdsize;
		++i;
	}
	ft_putendl("didn't find nothing boss");
	return (NULL);
}
