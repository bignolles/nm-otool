/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_magic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 14:52:49 by marene            #+#    #+#             */
/*   Updated: 2016/08/23 16:44:47 by marene           ###   ########.fr       */
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
	}
	else if (magic_nb == MH_MAGIC_64)
	{
		env->handler = handle_64;
	}
	else
	{
		env->handler = NULL;
		return (NM_NOK);
	}
	return (NM_OK);
}
