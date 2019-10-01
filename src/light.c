#include "rt.h"

t_light	light_new(t_vec position, float intensity)
{
	t_light light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}