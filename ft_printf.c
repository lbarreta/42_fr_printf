/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreta <lbarreta@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 22:19:18 by lbarreta          #+#    #+#             */
/*   Updated: 2021/03/16 00:45:40 by lbarreta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

int		ft_putchar(const char *str)
{
	write(1, str, 1);
	return(1);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n == -2147483648)
	{
		ft_putchar("-2");
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar("-");
		n = n * -1;
	}
	if (n < 10)
	{
		c = n + '0';
		ft_putchar(&c);
		return;
	}
	else
		ft_putnbr(n / 10);
	c = (n % 10) + '0';
	ft_putchar(&c);
}

int		ft_countnbr(int n)
{
	int i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	i++;

	return (i);
}

void	ft_putunbr(unsigned int n)
{
	char	c;
	if (n < 10)
	{
		c = n + '0';
		ft_putchar(&c);
		return;
	}
	else
		ft_putnbr(n / 10);
	c = (n % 10) + '0';
	ft_putchar(&c);
}

int		ft_countunbr(unsigned int n)
{
	int i;

	i = 0;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	i++;

	return (i);
}

int		ft_printchar(char c)
{
	return (ft_putchar(&c));
}

int		ft_printstr(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i += ft_putchar(&str[i]);

	return(i);
}

int		ft_printint(int n)
{
	ft_putnbr(n);
	return (ft_countnbr(n));
}

int		ft_printuint(unsigned int n)
{
	ft_putunbr(n);
	return (ft_countunbr(n));
}

void	ft_puthex_ca(unsigned int n)
{
	unsigned int		val;
	char				*hex;

	hex = "0123456789ABCDEF";

	val = n;
	if (val < 16)
	{
		ft_putchar(&hex [val % 16]);
		return;
	}
	else
		ft_puthex_ca(val / 16);
	ft_putchar(&hex [val % 16]);
}

void	ft_puthex(unsigned int n)
{
	unsigned int	val;
	char			*hex;

	hex = "0123456789abcdef";

	val = n;
	if (val < 16)
	{
		ft_putchar(&hex [val % 16]);
		return;
	}
	else
		ft_puthex(val / 16);
	ft_putchar(&hex [val % 16]);
}

int		ft_countx(unsigned int n)
{
	int i;

	i = 0;
	while (n >= 16)
	{
		n = n / 16;
		i++;
	}
	i++;

	return (i);
}

int		ft_printx(unsigned int n, char conv)
{
	if (conv == 'x')
		ft_puthex(n);
	else
		ft_puthex_ca(n);
	return (ft_countx(n));
}

int		ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	va_start(args, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == 'c')
				count += ft_printchar(va_arg(args, int));
			else if (str[i] == 's')
				count += ft_printstr(va_arg(args, const char *));
			else if (str[i] == 'd' || str[i] == 'i')
				count += ft_printint(va_arg(args, int));
			else if (str[i] == 'u')
				count += ft_printuint(va_arg(args, unsigned int));
			else if (str[i] == 'x' || str[i] == 'X')
				count += ft_printx(va_arg(args, unsigned int), str[i]);
			i++;
		}
		count += ft_putchar(&str[i]);
		i++;
	}
	//va_copy();
	va_end(args);
	return (count);
}


int		main ()
{
	int var_a = 2584;
	int var_b = -2584;
	int *ptr = &var_a;

	printf("%d\n", printf("bbb%cbbb ", 'a'));
	printf("%d\n\n", ft_printf("bbb%cbbb ", 'a'));

	printf("%d\n", printf("bbb%sbbb ", "aaa"));
	printf("%d\n\n", ft_printf("bbb%sbbb ", "aaa"));

	printf("%d\n", printf("bbb%dbbb ", -2147483647));
	printf("%d\n\n", ft_printf("bbb%dbbb ", -2147483647));

	printf("%d\n", printf("bbb%ibbb ", -533));
	printf("%d\n\n", ft_printf("bbb%ibbb ", -533));

	printf("%d\n", printf("bbb%ubbb ", -1));
	printf("%d\n\n", ft_printf("bbb%ubbb ", -1));

	printf("%d\n", printf("bbb%xbbb ", var_a));
	printf("%d\n\n", ft_printf("bbb%xbbb ", var_a));

	printf("%d\n", printf("bbb%xbbb ", var_b));
	printf("%d\n\n", ft_printf("bbb%xbbb ", var_b));

	printf("%d\n", printf("bbb%Xbbb ", var_a));
	printf("%d\n\n", ft_printf("bbb%Xbbb ", var_a));

	printf("%d\n", printf("bbb%Xbbb ", var_b));
	printf("%d\n\n", ft_printf("bbb%Xbbb ", var_b));

	printf("%d\n", printf("bbb%pbbb ", ptr));
	//printf("%d\n\n", ft_printf("bbb%pbbb ", ptr));

	return (0);
}
