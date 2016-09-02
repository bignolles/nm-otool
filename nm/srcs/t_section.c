/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_section.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 13:15:19 by marene            #+#    #+#             */
/*   Updated: 2016/09/02 14:32:04 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_file.h"

t_section				*t_section_construct_32(struct section *sect)
{
	t_section		*ret;

	if ((ret = malloc(sizeof(t_section))) != NULL)
	{
		ret->sectname = ft_strdup(sect->sectname);
		ret->segname = ft_strdup(sect->segname);
		if (ft_strequ(ret->segname, "__TEXT")
				&& ft_strequ(ret->sectname, "__text"))
			ret->secsym = 't';
		else if (ft_strequ(ret->segname, "__DATA")
				&& ft_strequ(ret->sectname, "__data"))
			ret->secsym = 'd';
		else if (ft_strequ(ret->segname, "__DATA")
				&& ft_strequ(ret->sectname, "__bss"))
			ret->secsym = 'b';
		else
			ret->secsym = 's';
	}
	return (ret);
}

t_section				*t_section_construct_64(struct section_64 *sect)
{
	t_section		*ret;

	if ((ret = malloc(sizeof(t_section))) != NULL)
	{
		ret->sectname = ft_strdup(sect->sectname);
		ret->segname = ft_strdup(sect->segname);
		if (ft_strequ(ret->segname, "__TEXT")
				&& ft_strequ(ret->sectname, "__text"))
			ret->secsym = 't';
		else if (ft_strequ(ret->segname, "__DATA")
				&& ft_strequ(ret->sectname, "__data"))
			ret->secsym = 'd';
		else if (ft_strequ(ret->segname, "__DATA")
				&& ft_strequ(ret->sectname, "__bss"))
			ret->secsym = 'b';
		else
			ret->secsym = 's';
	}
	return (ret);
}
