#include "rt.h"

int 	out_of_borders(int x, int y)
{
	if (x < 0 || x > SCREEN_W - 1)
		return (1);
	if (y < 0 || y > SCREEN_H - 1)
		return (1);
	return (0);
}

void	set_pixel(SDL_Surface *surface, int x, int y, t_color *c)
{
	int		offset;

	if (out_of_borders(x, y)
		return ;
	offset = 4 * (y * surface -> w + x);
	unsigned char* pixels = (unsigned char*)surface->pixels;
	pixels[offset] = c->b;
	pixels[offset + 1] = c->g;
	pixels[offset + 2] = c->r;
}