/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:18:06 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:18:16 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		out_of_border(int x, int y)
{
	if (x < 0 || x > WIDTH - 1)
		return (1);
	if (y < 0 || y > HEIGHT - 1)
		return (1);
	return (0);
}

void	set_pixel(SDL_Surface *surface, int x, int y, t_color c)
{
	int				offset;
	unsigned char	*pixels;

	if (out_of_border(x, y))
		return ;
	offset = 4 * (y * surface->w + x);
	pixels = (unsigned char*)surface->pixels;
	pixels[offset] = c.b;
	pixels[offset + 1] = c.g;
	pixels[offset + 2] = c.r;
}
