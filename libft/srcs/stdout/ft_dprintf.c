/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:04:49 by rgramati          #+#    #+#             */
/*   Updated: 2024/02/23 15:24:53 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format(int fd, va_list args, char c)
{
	if (c == 'c')
		return (ft_putchar_fd(fd, va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr_fd(fd, va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putnbr_hex_fd(fd, va_arg(args, unsigned long), 0b10, 0));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(fd, va_arg(args, int)));
	else if (c == 'u')
		return (ft_putunbr_fd(fd, va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_putnbr_hex_fd(fd, va_arg(args, unsigned int), 0b00, 0));
	else if (c == 'X')
		return (ft_putnbr_hex_fd(fd, va_arg(args, unsigned int), 0b01, 0));
	else if (c == '%')
		return (write(fd, "%", 1));
	return (0);
}

int	ft_printer(int fd, const char *format, va_list args)
{
	char	*tmp;
	int		len;

	tmp = (char *)format;
	len = 0;
	while (*tmp)
	{
		if (*tmp == '%' && ft_strchr("cspdiuxX%", *(tmp + 1)))
			len += ft_format(fd, args, *(tmp++ + 1));
		else if (*tmp != '%')
			len += ft_putchar_fd(fd, *tmp);
		tmp++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		len;
	va_list	args;

	if (!format)
		return (-1);
	va_start(args, format);
	len = ft_printer(1, format, args);
	va_end(args);
	return (len);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int		len;
	va_list	args;

	if (!format)
		return (-1);
	va_start(args, format);
	len = ft_printer(fd, format, args);
	va_end(args);
	return (len);
}
