/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_text_section.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 16:03:57 by marene            #+#    #+#             */
/*   Updated: 2016/09/01 16:15:33 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void				*get_text_section(void *file)
{
	handler		handle;

	handle = get_handler(file);
	if (handle == NULL)
		return (NULL);
	else
		return (handle(file));
}
