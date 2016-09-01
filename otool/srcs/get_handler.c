/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 16:09:35 by marene            #+#    #+#             */
/*   Updated: 2016/09/01 17:51:49 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

handler				get_handler(void *file)
{
	uint32_t	magic;

	magic = *(uint32_t*)file;
	if (magic == MH_MAGIC)
		return (handle_32);
	else if (magic == MH_MAGIC_64)
		return (handle_64);
	else
		return (NULL);
}
