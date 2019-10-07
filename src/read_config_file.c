#include "rt.h"

int		num_elem(char **tab)
{
	int		count;

	count = 0;
	while (tab[count] != NULL)
	{
		count++;
	}
	return (count);
}

int		check_elem(char **tab, int flag)
{
	if (flag == 1)
	{
		if (num_elem(tab) != 7)
			return (FALSE);
		scene_set_camera(tab);
	}
	if (flag == 2)
	{
		if (num_elem(tab) != 5)
			return (FALSE);
		scene_set_light(tab);
	}
	if (flag == 3)
	{
		if (num_elem(tab) != 7)
			return (FALSE);
		scene_set_plane(tab);
	}
	if (flag == 4)
	{
		if (num_elem(tab) != 5)
			return (FALSE);
		scene_set_sphere(tab);
	}
	if (flag == 5)
	{
		if (num_elem(tab) != 8)
			return (FALSE);
		scene_set_cone(tab);
	}
	if (flag == 6)
	{
		if (num_elem(tab) != 8)
			return (FALSE);
		scene_set_cylinder(tab);
	}
	return (TRUE);
}

int		check_draft(char **draft_obj, t_app *app)
{
	if (ft_strequ(draft_obj[1], "camera"))
		if (!check_elem(draft_obj, 1))
			return (FALSE);
	if (ft_strequ(draft_obj[1], "light"))
		if (!check_elem(draft_obj, 2))
			return (FALSE);
	if (ft_strequ(draft_obj[1], "plane"))
		if (!check_elem(draft_obj, 3))
			return (FALSE);
	if (ft_strequ(draft_obj[1], "sphere"))
		if (!check_elem(draft_obj, 4))
			return (FALSE);
	if (ft_strequ(draft_obj[1], "cone"))
		if (!check_elem(draft_obj, 5))
			return (FALSE);
	if (ft_strequ(draft_obj[1], "cylinder"))
		if (!check_elem(draft_obj, 6))
			return (FALSE);
	return (TRUE);
}

void	read_config(t_app *app, char *path)
{
	int		fd;
	char	*line;
	char	**draft_obj;

	fd = open(path, O_RDONLY);

	while (ft_gnl(fd, &line) > 0)
	{
		draft_obj = ft_strsplit(line, ' ');
		if (!check_draft(draft_obj, app))
			continue ;
//		write_obj()
		free(line);
	}
	close(fd);
}