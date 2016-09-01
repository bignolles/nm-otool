#ifndef FT_NM
# define FT_NM

# include <stdlib.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/stab.h>
# include "t_file.h"
# include "libft.h"

# define NM_OK		0
# define NM_NOK		1

typedef int			(*file_handler)(t_file *file);

typedef struct		s_env
{
	t_file			*froot;
	file_handler	handler;
}					t_env;

t_env					g_foo;

int					handle_32(t_file *file);
int					handle_64(t_file *file);
t_env				*init_env(void);
int					env_next_file(t_env *env);
int					load_file(char *file_name, t_file **froot);
int					get_magic(t_env *env);
int					symsort_ascii(t_symbol *s1, t_symbol *s2);

#endif
