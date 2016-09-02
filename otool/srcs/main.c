/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 13:07:20 by marene            #+#    #+#             */
/*   Updated: 2016/09/02 13:27:28 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void		init(t_env *env)
{
	//munmap previous file
	env->file = NULL;
	env->text= NULL;
	env->addr64 = 0;
	env->addr32 = 0;
}

int				main(int argc, char **argv)
{
	int			i;
	t_env		env;

	i = 1;
	while (i < argc)
	{
		init(&env);
		if ((load_file(argv[i], &env)) == OTOOL_NOK)
			return (1);
		else
			print_text(&env);
		++i;
	}
}
