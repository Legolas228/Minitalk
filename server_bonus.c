/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:20:57 by pborrull          #+#    #+#             */
/*   Updated: 2024/01/24 09:21:04 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "printf/ft_printf.h"

char	*do_malloc(int c, char *str)
{
	str = malloc(sizeof(char *) * c);
	if (!str)
		exit (0);
	return (str);
}

int	show_msg(int c)
{
	static int	flag;
	static int	i;
	static char	*str;
	static int	len;

	if (flag != 1)
	{
		len = c;
		str = do_malloc(c, str);
		str[len] = '\0';
		flag = 1;
	}
	else
	{
		str[i++] = c;
		if (i == len)
		{
			write (1, str, i);
			i = 0;
			flag = 0;
			free (str);
			return (-1);
		}
	}
	return (1);
}

void	read_msg(int signal)
{
	static int	bit;
	static int	c;
	static int	flag;

	if (signal == SIGUSR2 && flag != 1)
		c += 1 << (31 - bit);
	else if (signal == SIGUSR2)
		c += 1 << (7 - bit);
	bit++;
	if (bit == 32)
	{
		show_msg(c);
		flag = 1;
		bit = 0;
		c = 0;
	}
	if (bit == 8 && flag == 1)
	{
		flag = show_msg(c);
		c = 0;
		bit = 0;
	}
	return ;
}

int	main(void)
{
	ft_printf("%d\n", getpid());
	while (1)
	{
		signal (SIGUSR1, read_msg);
		signal (SIGUSR2, read_msg);
		pause ();
	}
	return (0);
}
