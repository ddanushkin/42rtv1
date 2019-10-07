/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:19:22 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:19:22 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	vec_new(double x, double y, double z)
{
	t_vec	new_v;

	new_v.x = x;
	new_v.y = y;
	new_v.z = z;
	return (new_v);
}

t_vec	vec_point_at(t_ray ray, double length)
{
	return (vec_add(ray.o, vec_mul_by(ray.d, length)));
}
