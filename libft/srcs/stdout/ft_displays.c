/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_displays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:36:21 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/23 14:36:32 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putchar_fd(int fd, char c)
{
	return (write(fd, &c, 1));
}

size_t	ft_putstr_fd(int fd, char *str)
{
	if (!str)
		return (write(fd, "(null)", 6));
	return (write(fd, str, ft_strlen(str)));
}

size_t	ft_putnbr_fd(int fd, long nb)
{
	size_t	len;

	len = 0;
	if (nb < 0)
	{
		nb = -nb;
		return (ft_putchar_fd(fd, '-') + ft_putnbr_fd(fd, nb));
	}
	if (nb >= 10)
		len = ft_putnbr_fd(fd, nb / 10);
	len += ft_putchar_fd(fd, (char){nb % 10 + 48});
	return (len);
}

size_t	ft_putnbr_hex_fd(int fd, unsigned long nb, int flags, int depth)
{
	size_t	len;

	len = 0;
	if (!nb && (flags & 0b10))
		return (ft_putstr_fd(fd, "(nil)"));
	if ((flags & 0b10) && depth == 0)
		len = ft_putstr_fd(fd, "0x");
	if (nb >= 16)
		len += ft_putnbr_hex_fd(fd, nb / 16, flags, depth + 1);
	if (flags & 0b01)
		len += ft_putchar_fd(fd, "0123456789ABCDEF"[nb % 16]);
	else
		len += ft_putchar_fd(fd, "0123456789abcdef"[nb % 16]);
	return (len);
}

size_t	ft_putunbr_fd(int fd, unsigned long nb)
{
	size_t	len;

	len = 0;
	if (nb >= 10)
		len = ft_putunbr_fd(fd, nb / 10);
	len += ft_putchar_fd(fd, (char){nb % 10 + 48});
	return (len);
}
