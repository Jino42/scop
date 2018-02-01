/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 22:15:26 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/02/01 21:40:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# define NB_MAT 4

# define MAT_EMERALD(mat) mat->ambient = vector_construct(0.0215f, 0.1745f, 0.0215f); \
							mat->diffuse = vector_construct(0.07568f, 0.61424f, 0.07568f); \
							mat->specular = vector_construct(0.633f, 0.727811f, 0.633f); \
							mat->shininess = 76.8f;
# define MAT_PR(mat) mat->ambient = vector_construct(0.8f, 0.2f, 0.4f); \
						mat->diffuse = vector_construct(0.8f, 0.2f, 0.4f); \
						mat->specular = vector_construct(0.8f, 0.2f, 0.4f); \
						mat->shininess = 32.f;
							/*
# define MAT_PEARL (t_material){{0.25f, 0.20725f, 0.20725f, 0.f}, \
							{0.1f, 0.829f, 0.829f, 0.f}, \
							{0.296648f, 0.296648f, 0.296648f, 0.f}, \
						 	0.11264f};
# define MAT_JADE (t_material){{0.135f, 0.2225f, 0.1575f, 0.f}, \
							{0.54f, 0.89f, 0.63f, 0.f}, \
							{0.316228f, 0.316228f, 0.316228f, 0.f}, \
						 	12.8f};
# define MAT_RED_PLASTIC (t_material){{0.f, 0.f, 0.f, 0.f}, \
							{0.5f, 0.f, 0.f, 0.f}, \
							{0.7f, 0.6f, 0.6f, 0.f}, \
							32.f};

*/
# define F_MAT_EMERALD (0)
# define F_MAT_PEARL (1)
# define F_MAT_JADE (2)
# define F_MAT_PR (3)
# define F_MAT_RED_PLASTIC (3)

# define MATERIAL_MAP_AMBIENT (1 << 0)
# define MATERIAL_MAP_DIFFUSE (1 << 1)
# define MATERIAL_MAP_SPECULAR (1 << 2)
# define MATERIAL_MAP_NORMAL (1 << 3)
# define MATERIAL_MAP_SHININESS (1 << 4)

#endif
