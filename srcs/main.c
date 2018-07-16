#include "scop.h"

int			main(int argc, char **argv)
{
	t_env *e;
	(void)argv;
	(void)argc;

	temp_json();

	if (!(e = env_construct()))
		return (ft_bool_error("Erreur: L'initialisation de t_env a échoué", NULL, NULL));
	loop(e);
	env_destruct(e);
	return (0);
}
