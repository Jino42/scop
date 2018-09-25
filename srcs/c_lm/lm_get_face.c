/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_get_face.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 21:20:39 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/25 21:25:59 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	lm_get_face_v(t_lm *lm)
{
	int ret;

	ret = sscanf(lm->line, "%s %i %i %i %i\n",
		lm->type, &lm->buffer_index_v[0], &lm->buffer_index_v[1],
		&lm->buffer_index_v[2], &lm->buffer_index_v[3]);
	if (ret != 4 && ret != 5)
		return (0);
	return (ret - 1);
}

static int	lm_get_face_v_vn(t_lm *lm)
{
	int ret;

	ret = sscanf(lm->line, "%s %i//%i %i//%i %i//%i %i//%i\n", lm->type,
							&lm->buffer_index_v[0], &lm->buffer_index_vn[0],
							&lm->buffer_index_v[1], &lm->buffer_index_vn[1],
							&lm->buffer_index_v[2], &lm->buffer_index_vn[2],
							&lm->buffer_index_v[3], &lm->buffer_index_vn[3]);
	if (ret != 7 && ret != 9)
		return (0);
	return ((ret - 1) >> 1);
}

static int	lm_get_face_v_vt(t_lm *lm)
{
	int ret;

	ret = sscanf(lm->line, "%s %i/%i %i/%i %i/%i %i/%i\n", lm->type,
							&lm->buffer_index_v[0], &lm->buffer_index_vt[0],
							&lm->buffer_index_v[1], &lm->buffer_index_vt[1],
							&lm->buffer_index_v[2], &lm->buffer_index_vt[2],
							&lm->buffer_index_v[3], &lm->buffer_index_vt[3]);
	if (ret != 7 && ret != 9)
		return (0);
	return ((ret - 1) >> 1);
}

static int	lm_get_face_v_vn_vt(t_lm *lm)
{
	int ret;

	ret = sscanf(lm->line, "%s %i/%i/%i %i/%i/%i %i/%i/%i %i/%i/%i\n", lm->type,
	&lm->buffer_index_v[0], &lm->buffer_index_vt[0], &lm->buffer_index_vn[0],
	&lm->buffer_index_v[1], &lm->buffer_index_vt[1], &lm->buffer_index_vn[1],
	&lm->buffer_index_v[2], &lm->buffer_index_vt[2], &lm->buffer_index_vn[2],
	&lm->buffer_index_v[3], &lm->buffer_index_vt[3], &lm->buffer_index_vn[3]);
	if (ret != 10 && ret != 13)
		return (0);
	if (ret == 10)
		return (3);
	return (4);
}

bool		lm_get_face(t_lm *lm)
{
	int ret;

	ret = 0;
	if (lm->mesh->flag == SCOP_V)
		ret = lm_get_face_v(lm);
	if (lm->mesh->flag == (SCOP_V | SCOP_VN))
		ret = lm_get_face_v_vn(lm);
	if (lm->mesh->flag == (SCOP_V | SCOP_VT))
		ret = lm_get_face_v_vt(lm);
	if (lm->mesh->flag == (SCOP_V | SCOP_VN | SCOP_VT))
		ret = lm_get_face_v_vn_vt(lm);
	if (!ret)
		return (false);
	lm_indexing_face(lm, lm->mesh, ret);
	return (true);
}
