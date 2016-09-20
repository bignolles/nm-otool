/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 15:49:32 by marene            #+#    #+#             */
/*   Updated: 2016/09/20 14:56:06 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int			load_file(char *filename, t_env *env)
{
	int				fd;
	struct stat		buff;

	if (filename && (fd = open(filename, O_RDONLY)) >= 0
			&& fstat(fd, &buff) == 0)
	{
		if ((env->file = mmap(NULL, buff.st_size,
						PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return (OTOOL_NOK);
		close(fd);
		env->start = env->file;
		env->filename = filename;
		env->filesize = buff.st_size;
		return ((get_text_section(env)));
	}
	return (OTOOL_NOK);
}
