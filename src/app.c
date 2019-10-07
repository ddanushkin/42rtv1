/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:06:05 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:06:05 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	app_set_position(t_app *app, int x, int y, int z)
{
	app->pos = vec_new(x, y, z);
}

void	app_set_rotation(t_app *app, int x, int y, int z)
{
	app->rot = vec_new(x, y, z);
}
