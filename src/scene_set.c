/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_0_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:19:52 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:19:52 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	scene_set_sphere(t_scene *scene, t_vec position, double radius)
{
	int		*c;

	c = &scene->counts[0];
	scene->spheres[c[SPHERE_OBJ]++] = sphere_new(
			position,
			radius);
}

void	scene_set_cone(t_scene *scene, t_vec position, t_vec rotation, double angle)
{
	int		*c;

	c = &scene->counts[0];
	scene->cones[c[CONE_OBJ]++] = cone_new(
			position,
			rotation,
			angle);
}

void	scene_set_cylinder(t_scene *scene, t_vec position, t_vec rotation, double radius)
{
	int		*c;

	c = &scene->counts[0];
	scene->cylinders[c[CYLINDER_OBJ]++] = cylinder_new(
			position,
			rotation,
			radius);
}

void	scene_set_plane(t_scene *scene, t_vec position, t_vec rotation)
{
	int		*c;

	c = &scene->counts[0];
	scene->planes[c[PLANE_OBJ]++] = plane_new(
			position,
			rotation);
}

void	scene_set_light(t_scene *scene, t_vec position, double intensity)
{
	int		*c;

	c = &scene->counts[0];
	scene->lights[c[LIGHT_OBJ]++] = light_new(
			position,
			intensity);
}