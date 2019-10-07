/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofrost-g <ofrost-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:17:04 by ofrost-g          #+#    #+#             */
/*   Updated: 2019/10/07 16:17:04 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_material	mat_new(double a_0, double a_1, double exp, t_color color)
{
	t_material	mat;

	mat.a0 = a_0;
	mat.a1 = a_1;
	mat.c = color;
	mat.exp = exp;
	return (mat);
}
