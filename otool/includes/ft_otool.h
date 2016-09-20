/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 13:08:05 by marene            #+#    #+#             */
/*   Updated: 2016/09/20 14:11:41 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <ar.h>
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
	void		*start;
	void		*text;
	char		*filename;
	uint32_t	filesize;
	uint64_t	addr64;
	uint64_t	addr32;
	uint64_t	size;
	uint8_t		print64;
}								t_env;

typedef int						(*t_handler)(t_env *env);

int								load_file(char *file_name, t_env *env);
int								get_text_section(t_env *env);
t_handler						get_handler(t_env *env);
int								handle_64(t_env *env);
int								handle_32(t_env *env);
int								handle_fat(t_env *env);
int								handle_ar(t_env *env);
void							print_text(t_env *env);
struct fat_header				reverse_fat_header(struct fat_header *fat_h);
struct fat_arch					reverse_fat_arch(struct fat_arch *f);

#endif
