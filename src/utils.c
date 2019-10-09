/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:19:23 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/09 16:34:11 by lglover          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	set_axis(t_vec *axis, t_vec rot)
{
	t_vec	tmp_1;
	t_vec	tmp_2;

	rot.y *= M_PI / 180.0;
	rot.x *= M_PI / 180.0;
	rot.z *= M_PI / 180.0;
	tmp_1 = vec_new(0.0, -1.0, 0.0);
	tmp_2 = tmp_1;
	tmp_1.x = tmp_2.x * cos(rot.z) - tmp_2.y * sin(rot.z);
	tmp_1.y = tmp_2.x * sin(rot.z) + tmp_2.y * cos(rot.z);
	tmp_2 = tmp_1;
	tmp_1.y = tmp_2.y * cos(rot.x) - tmp_2.z * sin(rot.x);
	tmp_1.z = tmp_2.y * sin(rot.x) + tmp_2.z * cos(rot.x);
	tmp_2 = tmp_1;
	tmp_1.x = tmp_2.x * cos(rot.y) + tmp_2.z * sin(rot.y);
	tmp_1.z = -tmp_2.x * sin(rot.y) + tmp_2.z * cos(rot.y);
	*axis = vec_normalize(tmp_1);
}

void	set_view(t_vec *axis, t_vec rot)
{
	t_vec	tmp_1;
	t_vec	tmp_2;

	rot.y *= M_PI / 180.0;
	rot.x *= M_PI / 180.0;
	rot.z *= M_PI / 180.0;
	tmp_1 = *axis;
	tmp_2 = tmp_1;
	tmp_1.x = tmp_2.x * cos(rot.z) - tmp_2.y * sin(rot.z);
	tmp_1.y = tmp_2.x * sin(rot.z) + tmp_2.y * cos(rot.z);
	tmp_2 = tmp_1;
	tmp_1.y = tmp_2.y * cos(rot.x) - tmp_2.z * sin(rot.x);
	tmp_1.z = tmp_2.y * sin(rot.x) + tmp_2.z * cos(rot.x);
	tmp_2 = tmp_1;
	tmp_1.x = tmp_2.x * cos(rot.y) + tmp_2.z * sin(rot.y);
	tmp_1.z = -tmp_2.x * sin(rot.y) + tmp_2.z * cos(rot.y);
	*axis = vec_normalize(tmp_1);
}

double	calc_abc(double a, double b, double c)
{
	double t1;
	double t2;
	double ax2;
	double d;

	d = b * b - 4 * (a * c);
	if (fabs(d) < 0.001)
		return (MAX_DIST);
	if (d < 0.0)
		return (MAX_DIST);
	d = sqrt(d);
	ax2 = (2 * a);
	t1 = (-b - d) / ax2;
	t2 = (-b + d) / ax2;
	if (t1 < 0.0)
		t1 = t2;
	if (t1 < 0.0)
		return (MAX_DIST);
	return (t1);
}

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
