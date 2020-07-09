/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antomart <antomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 12:09:04 by antomart          #+#    #+#             */
/*   Updated: 2020/07/09 12:28:19 by antomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

ssize_t ft_strlen(char *str)
{
	size_t i;
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_numlen(long long n, int base_len)
{
	int i;
	i = 1;
	while (n >= base_len || n <= -base_len)
	{
		n = n / base_len;
		i++;
	}
	return (i);
}

void ft_putnum(long long n, int base_len, char *base)
{
	if (n >= base_len)
		ft_putnum(n / base_len, base_len, base);
	write(1, &base[n % base_len], 1);
}

int ft_printf(char *format, ...)
{
	va_list args;
	char *str;
	char *s;
	char *base;
	long int num;
	int width = 0;
	int prec = 0;
	int ret = 0;
	int neg = 0;
	int zero = 0;
	int dot = 0;
	int pad = 0;
	int nlen = 0;
	int base_len;
	va_start(args, format);
	str = (char *)format;
	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			width = 0;
			prec = 0;
			pad = 0;
			zero = 0;
			dot = 0;
			nlen = 0;
			neg = 0;
			while (*str >= '0' && *str <= '9')
			{
				width = width * 10 +(*str - '0');
				str++;
			}
			if (*str == '.')
			{
				str++;
				while (*str >= '0' && *str <= '9')
				{
					prec = prec * 10 +(*str - '0');
					str++;
				}
				dot = 1;
			}
			if (*str == 's')
			{
				s = va_arg(args, char *);
				if (!s)
					s = "(null)";
				nlen = ft_strlen(s); 
			}
			if (*str == 'x')
			{
				num = va_arg(args, unsigned);
				base = "0123456789abcdef";
				base_len = 16;
				nlen = ft_numlen(num, base_len);
			}
			if (*str == 'd')
			{
				num = va_arg(args, int);
				if (num < 0)
				{
					num = num * -1;
					neg = 1;
				}
				base = "0123456789";
				base_len = 10;
				nlen = ft_numlen(num, base_len) + neg;
			}
			if (dot == 1 && prec > nlen && *str != 's')
				zero = prec - nlen + neg;
			else if (dot == 1 && prec < nlen && *str == 's')
				nlen = prec;
			else if (dot == 1 && prec == 0 && (*str == 's' || num == 0))
				nlen = 0;
			pad = width - nlen - zero;
			while (pad-- >0)
			{
				write(1, " ", 1);
				ret++;
			}
			if (neg == 1)
				write(1, "-", 1);
			while (zero-- > 0)
			{
				write(1, "0", 1);
				ret++;
			}
			if (*str == 's')
				write(1, s, nlen);
			else if (nlen > 0)
				ft_putnum(num, base_len, base);
			ret += nlen;
			str++;
		}
		else
		{
			write(1, str, 1);
			ret++;
			str++;
		}
	
	}
	return (ret);
}