#include "scop.h"

int			main(int argc, char **argv)
{
	t_env *e;

	if (!(e = env_construct(argc, argv)))
		return (ft_bool_error("Erreur: L'initialisation de t_env a échoué", NULL, NULL));
	loop(e);
	env_destruct(e);
	return (0);
}
