/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_random.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglover <lglover@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:22:02 by lglover           #+#    #+#             */
/*   Updated: 2019/10/09 13:24:03 by lglover          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	random_color(void)
{
	return (color_hsv(rand() % 360));
}

t_color	color_hsv(int hue)
{
	double	prime_color;
	t_color	c;

	prime_color = (1.0 - fabs(fmod(hue / 60.0, 2.0) - 1.0)) * 255.0;
	if (hue >= 0 && hue < 60)
		c = color_new(255, prime_color, 0);
	else if (hue >= 60 && hue < 120)
		c = color_new(prime_color, 255, 0);
	else if (hue >= 120 && hue < 180)
		c = color_new(0, 255, prime_color);
	else if (hue >= 180 && hue < 240)
		c = color_new(0, prime_color, 255);
	else if (hue >= 240 && hue < 300)
		c = color_new(prime_color, 0, 255);
	else
		c = color_new(255, 0, prime_color);
	return (c);
}
