/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_texture.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 14:08:20 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/09/19 14:08:45 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_TEXTURE_H
# define C_TEXTURE_H

# include "vector.h"
# include <stdint.h>

typedef struct		s_texture
{
	char			*name;
	GLuint			id;
	unsigned int	width;
	unsigned int	height;
	int				flag;
	unsigned char	*data;
}					t_texture;
void				*texture_destruct(t_texture **texture);
t_texture			*texture_construct(const char *name, const int type);
bool				texture_load_tga(t_texture *texture, const char *filename);

typedef struct		s_m_texture
{
	int				index_selected;
	unsigned int	size;
	t_texture		**texture;
	char			**texture_name;
	bool			(*add)(struct s_m_texture *, t_texture *);
	t_texture		*(*new)(struct s_m_texture *, const int type, const char *);
}					t_m_texture;

typedef struct		s_tga
{
	unsigned char	type_code;
	short int		width;
	short int		height;
	unsigned char	bit_count;
	unsigned char	*data;
	int				fd;
	char			buffer[255];
}					t_tga;

t_m_texture			*m_texture_construct();
void				*m_texture_destruct(t_m_texture **m_model);
bool				m_texture_json_parse(t_m_texture *m_texture,
						cJSON *get, const char *key);

#endif
