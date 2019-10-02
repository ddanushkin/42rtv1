#include "rt.h"

t_plane plane_new(t_vec pos, t_vec normal, t_material mat)
{
	t_plane	plane;

	plane.position = pos;
	plane.normal = normal;
	plane.mat = mat;
	return (plane);
}

double	plane_intersection(t_ray ray, t_vec pos, t_vec normal)
{
	double	denom;
	double	t;

	t = INFINITY;
	denom = vec_dot(ray.direction, normal);
	if (denom > 0.0000001)
		t = vec_dot(normal, vec_sub(pos,ray.origin)) / denom;
	return (t);
}

void	check_planes(t_scene scene, t_ray ray, t_hit *hit)
{
	int			i;
	double		dist;
	t_plane		plane;

	i = 0;
	while (i < scene.counts[COUNT_PLANES])
	{
		plane = scene.planes[i];
		dist = plane_intersection(ray, plane.position, plane.normal);
		if (dist < hit->d)
		{
			hit->m = plane.mat;
			hit->d = dist;
			hit->p = vec_point_at(ray.origin, ray.direction, dist);
			hit->n = vec_invert(plane.normal);
			hit->collided = TRUE;
		}
		i++;
	}
}
