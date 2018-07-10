/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_of_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:32:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/07 23:59:59 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	env_end(t_env *e)
{
	(void)e;
}

int			end_of_program(t_env *e, char *str, int flag)
{
	(void)flag;
	if (str)
		ft_dprintf(2, "%s\n", str);
	glfwTerminate();
	env_end(e);
	return (0);
}