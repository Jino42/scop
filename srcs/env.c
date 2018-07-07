#include "scop.h"

/*
** env_destruct est différente des autres destructeur.
** Pour garder la forme generique de ft_error
*/

void 	*env_destruct(void *ptr)
{
	t_env *e;

	e = (t_env *)ptr;
	if (e->glfw)
		glfw_destruct(&e->glfw);
	if (e->fps)
		fps_destruct(&e->fps);
	ft_memdel((void **)&e);
	return (NULL);
}

t_env 	*env_construct()
{
	t_env *e;

	if (!(e = ft_memalloc(sizeof(t_env))))
		return (NULL);
	if (!(e->glfw = glfw_construct("scop", 1920, 1080)) || 1)
		return (ft_error("Erreur: L'initialisation de t_glfw a échoué", &env_destruct, e));
	if (!(e->fps = fps_construct()))
		return (env_destruct(&e));
	return (e);
}
