/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 16:45:29 by marene            #+#    #+#             */
/*   Updated: 2016/08/30 15:31:10 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>

#include "ft_nm.h"

int		main(int argc, char **argv)
{
	t_env		*env;
	int			i;

	i = 1;
	if ((env = init_env()) != NULL)
	{
		while (i < argc)
		{
			if (load_file(argv[i], &(env->froot)) == T_FILE_NOK)
				return (1);
			++i;
		}
		while (env_next_file(env) == NM_OK)
			;
	}
}
