/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 18:37:04 by marene            #+#    #+#             */
/*   Updated: 2016/09/01 12:56:35 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void			putaddr32(uint32_t n, int fd)
{
	char			res[8];
	int				i;
	char			base16[16];

	ft_strcpy(base16, "0123456789abcdef");
	ft_memset(res, '0', 8);
	i = 8 - 1;
	while (n > 0 && i >= 0)
	{
		res[i] = base16[n % 16];
		n = n - (n % 16);
		n /= 16;
		i--;
	}
	write(fd, res, 8);
}

void			putaddr64(uint64_t n, int fd)
{
	char			res[16];
	int				i;
	char			base16[16];

	ft_strcpy(base16, "0123456789abcdef");
	ft_memset(res, '0', 18);
	i = 16 - 1;
	while (n > 0 && i >= 0)
	{
		res[i] = base16[n % 16];
		n = n - (n % 16);
		n /= 16;
		i--;
	}
	write(fd, res, 16);
}
