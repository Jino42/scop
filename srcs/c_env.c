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
	if (e->scene)
		scene_destruct(&e->scene);
	ft_memdel((void **)&e);
	return (NULL);
}

t_env 	*env_construct(int argc, char **argv)
{
	t_env *e;

	(void)argc;
	if (!(e = ft_memalloc(sizeof(t_env))))
		return (NULL);
	if (!(e->glfw = glfw_construct("scop", 1920, 1080)))
		return (ft_error("Erreur: L'initialisation de t_glfw a échoué", &env_destruct, e));
	if (!(e->fps = fps_construct()))
		return (ft_error("Erreur: L'initialisation de t_glfw a échoué", &env_destruct, e));
	if (!(e->scene = scene_construct(argv[1])))
		return (ft_error("Erreur: L'initialisation de t_scene a échoué", &env_destruct, e));
	return (e);
}
