/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 15:50:36 by marene            #+#    #+#             */
/*   Updated: 2016/08/22 16:03:04 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int				handle_64(t_file *file)
{
	struct mach_header_64		header;
	struct load_command			lc;
	uint32_t					ncmds;

	header = *(struct mach_header_64*)file->content;
	ncmds = header.ncmds;
	return (NM_OK);
}
