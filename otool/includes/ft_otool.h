/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 13:08:05 by marene            #+#    #+#             */
/*   Updated: 2016/09/01 18:52:01 by marene           ###   ########.fr       */
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

typedef void					*(*handler)(void *file);

void							*load_file(char *file_name);
void							*get_text_section(void *file);
handler							get_handler(void *file);
void							*handle_64(void *file);
void							*handle_32(void *file);
void							print_text(void *text);

#endif
