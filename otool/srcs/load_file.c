/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 15:49:32 by marene            #+#    #+#             */
/*   Updated: 2016/09/01 17:53:18 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void			*load_file(char *filename)
{
	int				fd;
	void			*file;
	struct stat		buff;

	if (filename && (fd = open(filename, O_RDONLY)) >= 0 && fstat(fd, &buff) == 0)
	{
		if ((file = mmap(NULL, buff.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return (NULL);
		close(fd);
		return ((get_text_section(file)));
	}
	return (NULL);
}
