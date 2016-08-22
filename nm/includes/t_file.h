/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 10:36:21 by marene            #+#    #+#             */
/*   Updated: 2016/08/22 15:26:24 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_FILE_H
# define T_FILE_H

# include <sys/stat.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define T_FILE_OK	0
# define T_FILE_NOK	1

typedef struct		s_file
{
	char			*content;
	size_t			size;
	char			*name;
	struct s_file	*next;
}					t_file;

t_file				*t_file_create(char *file_name, int fd);
int					t_file_add(t_file **froot, t_file *file);
void				t_file_destruct(t_file *file);

#endif
