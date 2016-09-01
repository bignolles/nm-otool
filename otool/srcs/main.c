/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 13:07:20 by marene            #+#    #+#             */
/*   Updated: 2016/09/01 18:51:45 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

int		main(int argc, char **argv)
{
	int			i;
	void		*text;

	i = 1;
	while (i < argc)
	{
		if ((text = load_file(argv[i])) == NULL)
			return (1);
		else
			print_text(text);
		++i;
	}
}
