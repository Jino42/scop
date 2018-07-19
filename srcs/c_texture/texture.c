#include "scop.h"

t_texture		*texture_construct(char *name)
{
	t_texture *texture;

	if (!(texture = ft_memalloc(sizeof(t_texture))))
		return (NULL);
	texture->name = strdup(name);
	return (texture);
}

void		*texture_destruct(t_texture **texture)
{
	if (texture && *texture)
	{
		ft_memdel((void **)(&(*texture)->name));
		ft_memdel((void **)texture);
	}
	return (NULL);
}
