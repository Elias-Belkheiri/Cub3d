/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:10:29 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/16 16:27:54 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_comps(t_components *comp)
{
	comp->map = NULL;
	comp->elements.n_texture = NULL;
	comp->elements.s_texture = NULL;
	comp->elements.w_texture = NULL;
	comp->elements.e_texture = NULL;
	comp->elements.f_color = NULL;
	comp->elements.c_color = NULL;
}

int	main(int argc, char *argv[])
{
	t_components	comp;

	if (argc != 2)
		return (printf(YEL "Usage: ./cub3d map.cub \n" RESET));
	if (!read_map(argv[1], &comp))
		return (printf("Invalid Map\n"));
}
