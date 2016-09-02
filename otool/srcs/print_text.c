/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 19:22:50 by marene            #+#    #+#             */
/*   Updated: 2016/09/02 13:35:40 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void				print_text(t_env *env)
{
	uint64_t		lines_nb;
	uint64_t		i;
	uint64_t		j;

	lines_nb = env->size / DUMP_INCREMENT + (env->size % DUMP_INCREMENT != 0);
	i = 0;
	ft_putstr(env->filename);
	ft_putendl(":");
	ft_putendl("(__TEXT,__text) section");
	while (i < lines_nb)
	{
		j = 0;
		putaddr64(env->addr64 + i * DUMP_INCREMENT, 1);
		ft_putchar(' ');
		while (j < DUMP_INCREMENT && i * DUMP_INCREMENT + j < env->size)
		{
			ft_putchar_hex(env->text + i * DUMP_INCREMENT + j);
			ft_putchar(' ');
			++j;
		}
		ft_putchar('\n');
		++i;
	}
}
