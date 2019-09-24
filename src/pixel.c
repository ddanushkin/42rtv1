#include "rt.h"

int 	out_of_border(int x, int y)
{
	if (x < 0 || x > WIDTH - 1)
		return (1);
	if (y < 0 || y > HEIGHT - 1)
		return (1);
	return (0);
}

t_color	get_pixel(SDL_Surface *surface, int x, int y)
{
	t_color color;
	int		offset;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 0;
	if (out_of_border(x, y))
		return (color);
	offset = 4 * (y * surface -> w + x);
	unsigned char* pixels = (unsigned char*)surface->pixels;
	color.a = pixels[offset + 3];
	color.r = pixels[offset + 2];
	color.g = pixels[offset + 1];
	color.b = pixels[offset];
	return (color);
}

void	set_pixel(SDL_Surface *surface, int x, int y, t_color c)
{
	int		offset;

	if (out_of_border(x, y))
		return ;
	offset = 4 * (y * surface -> w + x);
	unsigned char* pixels = (unsigned char*)surface->pixels;
	pixels[offset] = c.b;
	pixels[offset + 1] = c.g;
	pixels[offset + 2] = c.r;
}