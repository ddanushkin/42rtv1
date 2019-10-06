#include "rt.h"

void	print_usage()
{
	ft_putendl("Usage: RTv1 -s [scene_id] -p [x y z] -r [x y z]");
	ft_putendl("  s - Set scene to render.");
	ft_putendl("  p - Set camera position.");
	ft_putendl("  r - Set camera rotation.");
}