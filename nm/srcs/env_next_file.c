/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_next_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 15:19:07 by marene            #+#    #+#             */
/*   Updated: 2016/08/22 15:57:40 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int				env_next_file(t_env *env)
{
	t_file		*tmp;

	
	if (env->froot)
	{
		ft_putstr(env->froot->name);
		ft_putstr(" : ");
		if (get_magic(env) == NM_OK)
			env->handler(env->froot);
		tmp = env->froot;
		env->froot = env->froot->next;
		t_file_destruct(tmp);
		return (NM_OK);
	}
	return (NM_NOK);
}
