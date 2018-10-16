/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:58:59 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/10/16 23:15:46 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		lm_indexing_verif_range(t_lm *lm, const int sommet)
{
	if ((lm->mesh->flag & SCOP_V)
		&& ((lm->buffer_index_v[sommet] - 1) * 1 < 0
			|| (lm->buffer_index_v[sommet] - 1) * 1 >= lm->nb_v))
	{
		return (false);
	}
	if ((lm->mesh->flag & SCOP_VT)
		&& ((lm->buffer_index_vt[sommet] - 1) * 1 < 0
			|| (lm->buffer_index_vt[sommet] - 1) * 1 >= lm->nb_vt))
	{
		return (false);
	}
	if ((lm->mesh->flag & SCOP_VN)
		&& ((lm->buffer_index_vn[sommet] - 1) * 1 < 0
			|| (lm->buffer_index_vn[sommet] - 1) * 1 >= lm->nb_vn))
	{
		return (false);
	}
	return (true);
}

bool		lm_verif_file(t_lm *lm)
{
	if (!lm->nb_indices)
		return (false);
	return (true);
}
