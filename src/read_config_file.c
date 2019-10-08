/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 22:38:14 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 22:38:14 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_data(t_app *app, char **d)
{
	if (ft_strequ(d[0], "camera"))
		app_set_camera(app,
				vec_new(ft_atoi(d[1]), ft_atoi(d[2]), ft_atoi(d[3])),
				vec_new(ft_atoi(d[4]), ft_atoi(d[5]), ft_atoi(d[6])));
	else if (ft_strequ(d[0], "sphere"))
		scene_set_sphere(app->scenes,
				vec_new(ft_atoi(d[1]), ft_atoi(d[2]), ft_atoi(d[3])),
				ft_atoi(d[4]));
	else if (ft_strequ(d[0], "cone"))
		scene_set_cone(app->scenes,
				vec_new(ft_atoi(d[1]), ft_atoi(d[2]), ft_atoi(d[3])),
				vec_new(ft_atoi(d[4]), ft_atoi(d[5]), ft_atoi(d[6])),
				ft_atoi(d[7]));
	else if (ft_strequ(d[0], "cylinder"))
		scene_set_cylinder(app->scenes,
				vec_new(ft_atoi(d[1]), ft_atoi(d[2]), ft_atoi(d[3])),
				vec_new(ft_atoi(d[4]), ft_atoi(d[5]), ft_atoi(d[6])),
				ft_atoi(d[7]));
	else if (ft_strequ(d[0], "plane"))
		scene_set_plane(app->scenes,
				vec_new(ft_atoi(d[1]), ft_atoi(d[2]), ft_atoi(d[3])),
				vec_new(ft_atoi(d[4]), ft_atoi(d[5]), ft_atoi(d[6])));
	else if (ft_strequ(d[0], "light"))
		scene_set_light(app->scenes, vec_new(ft_atoi(d[1]), ft_atoi(d[2]),
				ft_atoi(d[3])), ft_atoi(d[4]));
}

void	parse_config(t_app *app, char *path)
{
	int		fd;
	char	*line;
	char	**data_obj;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl("Bad scene file.");
		safe_quit(app);
	}
	while (ft_gnl(fd, &line) > 0)
	{
		data_obj = ft_strsplit(line, ' ');
		ft_strdel(&line);
		parse_data(app, data_obj);
		ft_splitdel(&data_obj);
	}
}

void	scene_alloc(t_app *app, t_scene *scene)
{
	scene_add_spheres(
			scene,
			scene->counts[SPHERE_OBJ]);
	scene_add_cylinders(
			scene,
			scene->counts[CYLINDER_OBJ]);
	scene_add_cones(
			scene,
			scene->counts[CONE_OBJ]);
	scene_add_planes(
			scene,
			scene->counts[PLANE_OBJ]);
	scene_add_lights(
			scene,
			scene->counts[LIGHT_OBJ]);
	ft_memset(app->scenes->counts, 0, sizeof(int[5]));
}

int		check_draft(char **draft_obj, t_app *app)
{
	if (ft_strequ(draft_obj[0], "camera") && num_elem(draft_obj) == 7)
		return (TRUE);
	if (ft_strequ(draft_obj[0], "sphere") && num_elem(draft_obj) == 5)
		return (++app->scenes->counts[SPHERE_OBJ]);
	if (ft_strequ(draft_obj[0], "cone") && num_elem(draft_obj) == 8)
		return (++app->scenes->counts[CONE_OBJ]);
	if (ft_strequ(draft_obj[0], "cylinder") && num_elem(draft_obj) == 8)
		return (++app->scenes->counts[CYLINDER_OBJ]);
	if (ft_strequ(draft_obj[0], "plane") && num_elem(draft_obj) == 7)
		return (++app->scenes->counts[PLANE_OBJ]);
	if (ft_strequ(draft_obj[0], "light") && num_elem(draft_obj) == 5)
		return (++app->scenes->counts[LIGHT_OBJ]);
	return (FALSE);
}

void	read_config(t_app *app, char *path)
{
	int		fd;
	char	*line;
	char	**draft_obj;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl("Bad scene file.");
		safe_quit(app);
	}
	while (ft_gnl(fd, &line) > 0)
	{
		draft_obj = ft_strsplit(line, ' ');
		ft_strdel(&line);
		if (!check_draft(draft_obj, app))
		{
			ft_splitdel(&draft_obj);
			close(fd);
			safe_quit(app);
		}
		ft_splitdel(&draft_obj);
	}
	close(fd);
	scene_alloc(app, app->scenes);
	parse_config(app, path);
}
