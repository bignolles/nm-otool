/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_next_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 15:19:07 by marene            #+#    #+#             */
/*   Updated: 2016/09/09 12:10:55 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int				env_next_file(t_env *env)
{
	t_file		*tmp;

	if (env->froot)
	{
		if (get_magic(env) == NM_OK)
			env->handler(env->froot);
		if (env->froot != NULL)
		{
			tmp = env->froot;
			env->froot = env->froot->next;
			t_file_destruct(tmp);
		}
		return (NM_OK);
	}
	return (NM_NOK);
}
