/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_magic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 14:52:49 by marene            #+#    #+#             */
/*   Updated: 2016/08/22 15:22:37 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int				get_magic(t_env *env)
{
	unsigned int		magic_nb;

	magic_nb = *(int *)env->froot->content;
	if (magic_nb == MH_MAGIC)
	{
		env->handler = handle_32;
		ft_putendl("32 bits!");
	}
	else if (magic_nb == MH_MAGIC_64)
	{
		env->handler = handle_64;
		ft_putendl("64 bits!");
	}
	else
	{
		env->handler = NULL;
		ft_putendl("not a macho file :(");
		return (NM_NOK);
	}
	return (NM_OK);
}
