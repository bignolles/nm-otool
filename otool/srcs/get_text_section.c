/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_text_section.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 16:03:57 by marene            #+#    #+#             */
/*   Updated: 2016/09/02 13:05:33 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int				get_text_section(t_env *env)
{
	handler		handle;

	handle = get_handler(env->file);
	if (handle == NULL)
		return (OTOOL_NOK);
	else
		return (handle(env));
}
