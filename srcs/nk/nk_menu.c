/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nk_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 23:39:24 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/24 00:20:17 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop_nk.h"
#include "scop.h"

bool				nk_scene_menu(t_nk *nk, t_scene **scene)
{
	struct nk_context		*ctx;

	ctx = nk->ctx;
	if (nk_button_label(ctx, "Save"))
	{
		if (scene_write((*scene), (*scene)->path))
			dprintf(2, "Fichier enregistré !\n");
		else if (!scene_write((*scene), (*scene)->path))
			dprintf(2, "Une erreur c'est produite.\n");
	}
	return (true);
}
