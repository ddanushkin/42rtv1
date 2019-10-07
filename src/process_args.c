/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:19:54 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:19:54 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	args_check_pos(t_app *app, int argc, char **argv)
{
	app_set_position(app, 0, 0, 5);
	if (argc == 4)
		app_set_position(
			app,
			ft_atoi(argv[1]),
			ft_atoi(argv[2]),
			ft_atoi(argv[3]));
}

void	args_check_rot(t_app *app, int argc, char **argv)
{
	app_set_rotation(app, 0, 0, 0);
	if (argc == 7)
		app_set_rotation(
			app,
			ft_atoi(argv[4]),
			ft_atoi(argv[5]),
			ft_atoi(argv[6]));
}
