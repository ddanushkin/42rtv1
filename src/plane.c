/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:19:55 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:19:55 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_plane	plane_new(t_vec pos, t_vec rot, t_material mat)
{
	t_plane	plane;

	plane.pos = pos;
	plane.rot = rot;
	plane.mat = mat;
	set_axis(&plane.axis, plane.rot);
	return (plane);
}

double	plane_intersection(t_ray ray, t_plane plane)
{
	double	denom;
	double	t;

	t = INFINITY;
	denom = vec_dot(ray.d, plane.axis);
	if (denom > 0.0000001)
		t = vec_dot(plane.axis, vec_sub(plane.pos, ray.o)) / denom;
	return (t);
}

void	check_planes(t_scene scene, t_ray ray, t_hit *hit)
{
	int			i;
	double		dist;
	t_plane		plane;

	i = 0;
	while (i < scene.counts[PLANE_OBJ])
	{
		plane = scene.planes[i];
		dist = plane_intersection(ray, plane);
		if (dist < hit->d)
		{
			hit->m = plane.mat;
			hit->d = dist;
			hit->p = vec_point_at(ray, dist);
			hit->n = vec_invert(plane.axis);
			hit->collided = TRUE;
		}
		i++;
	}
}
