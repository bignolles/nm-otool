/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 10:36:21 by marene            #+#    #+#             */
/*   Updated: 2016/09/08 15:19:36 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_FILE_H
# define T_FILE_H

# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define T_FILE_OK	0
# define T_FILE_NOK	1

# define NM_SYM32	0x01
# define NM_SYM64	0x10

typedef struct		s_section
{
	char			*sectname;
	char			*segname;
	char			secsym;
}					t_section;

typedef struct		s_symbol
{
	char			*name;
	uint8_t			stab;
	uint8_t			pext;
	uint8_t			ext;
	uint8_t			type;
	int32_t			sectnb;
	uint32_t		n_value32; //test
	uint64_t		n_value64; //test
	uint64_t		n_value;
	uint8_t			byte;
}					t_symbol;

typedef struct		s_file
{
	void			*content;
	size_t			size;
	char			*name;
	t_section		**sections;
	t_symbol		**symbols;
	uint32_t		symbol_nb;
	struct s_file	*next;
}					t_file;

typedef int			(*t_symsort)(t_symbol *s1, t_symbol *s2);

t_file				*t_file_create(char *file_name, int fd);
int					t_file_add(t_file **froot, t_file *file);
void				t_file_destruct(t_file *file);
t_section			*t_section_construct_64(struct section_64 *sect);
t_section			*t_section_construct_32(struct section sect);
t_symbol			*t_symbol_construct_64(struct nlist_64 symtable,
						void *strtable);
t_symbol			*t_symbol_construct_32(struct nlist symtable,
						void *strtable);
int					sort_symbols(t_symbol **symbols, t_symsort sort);

#endif
