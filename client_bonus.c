/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:21:19 by pborrull          #+#    #+#             */
/*   Updated: 2024/01/24 09:21:24 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "printf/ft_printf.h"

void	send_len(int pid, int len)
{
	int	bits;

	bits = 31;
	while (bits >= 0)
	{
		if ((len >> bits) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(120);
		bits--;
	}
}

void	send(int pid, char *str)
{
	int	len;
	int	i;
	int	bits;

	i = 0;
	len = 0;
	while (str[len])
		len++;
	send_len(pid, len);
	while (i < len)
	{
		bits = 7;
		while (bits >= 0)
		{
			if ((str[i] >> bits) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(120);
			bits--;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	if (argc != 3)
		write(2, "Error\nPut the correct arguments\n", 32);
	else
	{
		pid = ft_atoi(argv[1]);
		if (pid < 1)
		{
			write(2, "Error\nInvalid PID\nTry it again!\n", 32);
			return (0);
		}
		str = argv[2];
		send(pid, str);
	}
	return (0);
}
