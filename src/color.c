/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:06:28 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:07:36 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	color_new(int r, int g, int b)
{
	t_color new_c;

	new_c.r = r;
	new_c.g = g;
	new_c.b = b;
	return (new_c);
}

void	color_clamp(t_color *c)
{
	c->r = CLAMP(c->r, 0, 255);
	c->g = CLAMP(c->g, 0, 255);
	c->b = CLAMP(c->b, 0, 255);
}

t_color	color_sum(t_color c1, t_color c2)
{
	t_color	new_c;

	new_c.r = c1.r + c2.r;
	new_c.g = c1.g + c2.g;
	new_c.b = c1.b + c2.b;
	return (new_c);
}

t_color	color_mul_by(t_color c, double k)
{
	t_color new_c;

	new_c.r = c.r * k;
	new_c.g = c.g * k;
	new_c.b = c.b * k;
	return (new_c);
}
