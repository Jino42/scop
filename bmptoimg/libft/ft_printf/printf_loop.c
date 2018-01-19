/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 14:54:56 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/09/12 16:34:05 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		init_struct(t_option *option)
{
	int i;

	i = -1;
	while (++i < 6)
		option->flags[i] = 0;
	option->prefix = NULL;
	option->final = NULL;
	option->before = NULL;
	option->word_c = NULL;
	option->word_w = NULL;
	option->width = 0;
	option->preci = 0;
	option->mod = 0;
	option->size_flags = 0;
	option->size_arg = 0;
	option->final_len = 0;
	option->sub_word = 0;
	option->sign = 1;
}

static int		check_type(char *str, t_option *option)
{
	if (*str == '%')
		write_percent(str, option);
	else if (option->mod != 0 && ft_isin("uoxX", *str))
		mod_uox(str, option);
	else if ((option->mod != 0 && ft_isin("di", *str)) || *str == 'D')
		mod_di(str, option);
	else if ((option->mod == 0 && ft_isin("dipouxX", *str))
			|| ft_isin("fFUOp", *str))
		dipfoux(str, option);
	else if (*str == 'c' || *str == 'C')
		sc_c(str, option);
	else if (*str == 's' || *str == 'S')
		sc_s(str, option);
	else if (option->width)
		write_other(str, option);
	else
		return (-1);
	option->final_len += option->width + option->size_flags
		+ option->size_arg;
	return (0);
}

static void		padd_arg(t_option *option, int *i, char *str)
{
	init_struct(option);
	(*i)++;
	while (ft_isdigit(str[*i]) || ft_isin(" #+-lhzj.*", str[*i]))
		*i += check_flags(&str[*i], option);
	*i += check_type(&str[*i], option);
	option->len += option->final_len;
	if (option->flag & FLAG_S)
		ft_reallocbuffer(option);
	else
		ft_putbuffer(option);
	ft_strdel(&option->final);
}

void			printf_loop(char *str, t_option *option)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
			padd_arg(option, &i, str);
		else if (str[i] != '%')
		{
			option->len++;
			if (option->flag & FLAG_S)
				ft_reallocbufferchar(str[i], option);
			else
				ft_putbufferchar(str[i], option);
		}
		i++;
	}
}
