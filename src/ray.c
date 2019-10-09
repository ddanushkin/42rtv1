/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:19:53 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/09 17:04:05 by lglover          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	ray_direction(t_app *app, int x, int y)
{
	t_vec	v;
	double	angle;

	angle = tanf(M_PI * 0.5 * app->fov / 180.0);
	v.x = 2.0 * ((double)x / (WIDTH - 1)) - 1.0;
	v.y = 1.0 - 2.0 * ((double)y / (HEIGHT - 1));
	v.x *= angle * app->asp_rat;
	v.y *= angle;
	v.z = -1.0;
	set_view(&v, app->rot);
	return (v);
}
