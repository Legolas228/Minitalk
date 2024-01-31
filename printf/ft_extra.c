/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:47:14 by pborrull          #+#    #+#             */
/*   Updated: 2024/01/18 15:18:50 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	signo;
	int	r;

	r = 0;
	i = 0;
	signo = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 45)
	{
		signo = -1;
		i ++;
	}
	else if (str[i] == 43)
		i ++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		r = r * 10 + (str[i] - '0');
		i ++;
	}
	r *= signo;
	return (r);
}

char	*ft_strchr(const char *s, int d)
{
	int		i;
	char	c;

	i = 0;
	c = (char)d;
	if (!s)
		return (NULL);
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == c)
		return ((char *)&s[i]);
	else
		return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (!str)
		return (count);
	while (str[count] != '\0')
		count ++;
	return (count);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	s2 = malloc(len + 1);
	if (s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i ++;
	}
	s2[i] = '\0';
	return (&s2[0]);
}

int	ft_while(const char *s, int i, int t, va_list list)
{
	while (*s)
	{
		if (*s != '%')
		{
			if (ft_printchar(*s++) < 1)
				return (-1);
			i++;
		}
		else if (ft_strchr("cspdiuxX%", *(s + 1)))
		{
			++s;
			t = ft_wall_if(list, *s);
			if (t == -1)
				return (-1);
			else
				i += t;
			++s;
		}
		else
			return (-1);
	}
	return (i);
}
