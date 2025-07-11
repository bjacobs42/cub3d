/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoahuge.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maxb <maxb@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 18:38:23 by mbernede      #+#    #+#                 */
/*   Updated: 2023/11/25 19:45:47 by maxb          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdarg.h>

char	*coppy(char *ptr, unsigned long div, unsigned long n,
unsigned long t)
{
	while (div > 0)
	{
		ptr[div + t - 1] = n % 10 + 48;
		n /= 10;
		--div;
	}
	return (ptr);
}

char	*allooc(unsigned long div)
{
	char	*ptr;

	++div;
	ptr = ft_calloc(div, 1);
	if (!ptr)
		return (NULL);
	return (ptr);
}

char	*ft_itoahuge(unsigned long n)
{
	char			*ptr;
	unsigned long	div;
	unsigned long	t;

	div = 1;
	t = n;
	while (t > 9)
	{
		t /= 10;
		++div;
	}
	ptr = allooc(div);
	if (!ptr)
		return (NULL);
	t = 0;
	ptr = coppy(ptr, div, n, t);
	return (ptr);
}

void	chars(int *result, char type, va_list liste)
{
	char	c;
	char	*ptr;

	if (type == 's')
	{
		ptr = va_arg(liste, char *);
		if (!ptr)
			ptr = "(null)";
		ft_putstr_fd(ptr, 1);
		*result += ft_strlen(ptr);
	}
	else if (type == 'c')
	{
		c = va_arg(liste, int);
		*result += write(1, &c, 1);
	}
}
