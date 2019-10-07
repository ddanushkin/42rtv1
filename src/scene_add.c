/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:19:47 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:19:47 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	scene_add_planes(t_scene *scene, int number)
{
	scene->planes = (t_plane *)malloc(sizeof(t_plane) * number);
}

void	scene_add_spheres(t_scene *scene, int number)
{
	scene->spheres = (t_sphere *)malloc(sizeof(t_sphere) * number);
}

void	scene_add_cones(t_scene *scene, int number)
{
	scene->cones = (t_cone *)malloc(sizeof(t_cone) * number);
}

void	scene_add_cylinders(t_scene *scene, int number)
{
	scene->cylinders = (t_cylinder *)malloc(sizeof(t_cylinder) * number);
}

void	scene_add_lights(t_scene *scene, int number)
{
	scene->lights = (t_light *)malloc(sizeof(t_light) * number);
}
