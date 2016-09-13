/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 10:38:21 by marene            #+#    #+#             */
/*   Updated: 2016/09/07 15:41:17 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_file.h"

t_file				*t_file_create(char *file_name, int fd)
{
	t_file			*ret;
	struct stat		buf;

	ret = NULL;
	if (fd >= 0 && fstat(fd, &buf) == 0)
	{
		if ((ret = malloc(sizeof(t_file))) != NULL)
		{
			ret->next = NULL;
			if ((ret->content = mmap(NULL, buf.st_size, PROT_READ,
							MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			{
				free(ret);
				ret = NULL;
			}
			else
			{
				ret->name = ft_strdup(file_name);
				ret->size = buf.st_size;
				ret->symbols = NULL;
				ret->sections = NULL;
			}
		}
	}
	return (ret);
}

int					t_file_add(t_file **froot, t_file *file)
{
	t_file	*it;

	if (*froot != NULL)
	{
		it = *froot;
		while (it->next != NULL)
			it = it->next;
		it->next = file;
	}
	else
		*froot = file;
	return (T_FILE_OK);
}

void				t_file_destruct(t_file *file)
{
	if (file != NULL)
	{
		if (file->content != NULL)
		{
			munmap(file->content, file->size);
			free(file->name);
		}
		free(file);
	}
}
