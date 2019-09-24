/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglover <lglover@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:18:20 by lglover           #+#    #+#             */
/*   Updated: 2019/09/19 13:16:30 by ofrost-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *ptr;

	if (alst == NULL || del == NULL)
		return ;
	while (*alst)
	{
		ptr = (*alst)->next;
		ft_lstdelone(&(*alst), del);
		(*alst) = ptr;
	}
	free(*alst);
	(*alst) = NULL;
}
