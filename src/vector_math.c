/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:19:20 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:19:20 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	vec_add(t_vec v1, t_vec v2)
{
	t_vec	new_v;

	new_v.x = v1.x + v2.x;
	new_v.y = v1.y + v2.y;
	new_v.z = v1.z + v2.z;
	return (new_v);
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	t_vec	new_v;

	new_v.x = v1.x - v2.x;
	new_v.y = v1.y - v2.y;
	new_v.z = v1.z - v2.z;
	return (new_v);
}

t_vec	vec_mul_by(t_vec v, double k)
{
	t_vec	new_v;

	new_v.x = v.x * k;
	new_v.y = v.y * k;
	new_v.z = v.z * k;
	return (new_v);
}
