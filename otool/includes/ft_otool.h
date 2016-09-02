/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 13:08:05 by marene            #+#    #+#             */
/*   Updated: 2016/09/02 14:28:17 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/mman.h>
# include "libft.h"

# define OTOOL_OK				0
# define OTOOL_NOK				1

# define O_SEGTEXT				"__TEXT"
# define O_SECTEXT				"__text"

# define DUMP_INCREMENT			0x10

typedef struct					s_env
{
	void		*file;
	void		*text;
	char		*filename;
	uint32_t	filesize;
	uint64_t	addr64;
	uint64_t	addr32;
	uint64_t	size;
}								t_env;

typedef int						(*t_handler)(t_env *env);

int								load_file(char *file_name, t_env *env);
int								get_text_section(t_env *env);
t_handler						get_handler(void *file);
int								handle_64(t_env *env);
int								handle_32(t_env *env);
void							print_text(t_env *env);

#endif
