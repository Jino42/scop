/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 00:27:05 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/10/16 22:29:39 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	*env_destruct(void *ptr)
{
	t_env *e;

	e = (t_env *)ptr;
	if (e->glfw)
		glfw_destruct(&e->glfw);
	if (e->fps)
		fps_destruct(&e->fps);
	if (e->scene)
		scene_destruct(&e->scene);
	ft_memdel((void **)&e);
	return (NULL);
}

t_env	*env_construct(int argc, char **argv)
{
	t_env *e;

	if (!(e = ft_memalloc(sizeof(t_env))))
		return (NULL);
	if (!(e->fps = fps_construct()))
	{
		return (ft_error("Error: t_fps cannot be initialised",
					&env_destruct, e));
	}
	if (!(e->glfw = glfw_construct("scop", 1920, 1080)))
	{
		return (ft_error("Error: t_glfw cannot be initialised",
					&env_destruct, e));
	}
	if (!strcmp(argv[1], "-debug_p"))
		e->debug = true;
	if (!(e->scene = scene_construct(argv[(argc == 3 ? 2 : 1)], argc >= 4)))
	{
		return (ft_error("Error: t_scene cannot be initialised",
					&env_destruct, e));
	}
	return (e);
}
