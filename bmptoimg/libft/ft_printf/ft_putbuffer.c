/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbuffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 19:33:18 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 16:34:09 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putbufferchar(char c, t_option *option)
{
	option->buffer[option->b] = c;
	option->b++;
	if (option->b == BUFF_SIZE_P)
	{
		write(option->fd, &option->buffer, option->b);
		option->b = 0;
	}
}

void	ft_putbuffer(t_option *option)
{
	int i;

	i = 0;
	while (i < option->final_len)
	{
		option->buffer[option->b] = option->final[i];
		option->b = option->b + 1;
		if (option->b == BUFF_SIZE_P)
		{
			write(option->fd, &option->buffer, option->b);
			option->b = 0;
		}
		i++;
	}
}

void	ft_reallocbufferchar(char c, t_option *option)
{
	if (!(option->b % BUFF_SIZE_P) && option->b != 0)
	{
		if (!(option->sbuffer = ft_memrealloc(option->sbuffer,
						option->b, option->b + BUFF_SIZE_P + 1)))
			exit(0);
	}
	option->sbuffer[option->b] = c;
	option->b = option->b + 1;
}

void	ft_reallocbuffer(t_option *option)
{
	int i;

	i = 0;
	while (i < option->final_len)
	{
		if (!(option->b % BUFF_SIZE_P) && option->b != 0)
		{
			if (!(option->sbuffer = ft_memrealloc(option->sbuffer,
						option->b, option->b + BUFF_SIZE_P + 1)))
				exit(0);
		}
		option->sbuffer[option->b] = option->final[i];
		option->b = option->b + 1;
		i++;
	}
}
