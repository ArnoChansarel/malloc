/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansar <achansar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:38:18 by achansar          #+#    #+#             */
/*   Updated: 2022/10/14 17:52:09 by achansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

static int	ft_putstr_printf(char *str)
{
	int	i;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (str[i])
		write(1, &str[i++], 1);
	return (i);
}

static int	ft_putnbr(int n)
{
	int	count;
	int	temp;

	count = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	temp = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		count++;
	}
	if (n >= 10)
	{
			count += ft_putnbr(n / 10);
			n = n % 10;
	}
	temp = n + 48;
	count++;
	write(1, &temp, 1);
	return (count);
}

static int	ft_putbase(unsigned long n, int c, unsigned int base)
{
	int				count;
	unsigned int	temp;

	count = 0;
	if (n >= base)
	{
		count += ft_putbase(n / base, c, base);
		n = n % base;
	}
	if (n >= 10 && n <= base && base == 16)
	{
		temp = n - 10 + c;
	}
	else
		temp = n + 48;
	count++;
	write(1, &temp, 1);
	return (count);
}

static int	ft_convert(int letter, int count, va_list args)
{
	if (letter == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (letter == 's')
		count += ft_putstr_printf(va_arg(args, char *));
	else if (letter == 'd')
		count += ft_putnbr(va_arg(args, int));
	else if (letter == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (letter == 'p')
	{
		write(1, "0x", 2);
		count += (ft_putbase(va_arg(args, unsigned long), 'a', 16) + 2);
	}
	else if (letter == 'u')
		count += ft_putbase(va_arg(args, unsigned int), 0, 10);
	else if (letter == 'x')
		count += ft_putbase(va_arg(args, unsigned int), 'a', 16);
	else if (letter == 'X')
		count += ft_putbase(va_arg(args, unsigned int), 'A', 16);
	else if (letter == '%')
	{
		write(1, "%", 1);
		count++;
	}
	return (count);
}


int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			count = ft_convert(str[i + 1], count, args);
			i += 2;
		}
		else
		{
			write(1, &str[i++], 1);
			count++;
		}
	}
	va_end(args);
	return (count);
}