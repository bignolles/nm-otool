/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 10:32:41 by marene            #+#    #+#             */
/*   Updated: 2016/08/22 15:01:01 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int					load_file(char *file_name, t_file **froot)
{
	int		fd;
	t_file	*new_file;

	if (file_name && (fd = open(file_name, O_RDONLY)) >= 0)
	{
		new_file = t_file_create(file_name, fd);
		close(fd);
		if (new_file != NULL)
			return (t_file_add(froot, new_file));
	}
	return (T_FILE_NOK);
}
