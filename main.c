/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:10:29 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/04/09 18:43:13 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_comps(t_components *comp)
{
	comp->map = NULL;
	comp->player_x = 0;
	comp->map_h = 0;
	comp->map_w = 0;
	comp->player_y = 0;
	comp->elements.n_texture = NULL;
	comp->elements.s_texture = NULL;
	comp->elements.w_texture = NULL;
	comp->elements.e_texture = NULL;
	comp->elements.f_color = 0;
	comp->elements.c_color = 0;
}

int	check_comps(t_components *comp)
{
	int	a;

	a = comp->elements.c_color && comp->elements.f_color
		&& comp->elements.n_texture && comp->elements.s_texture
		&& comp->elements.w_texture && comp->elements.e_texture
		&& comp->map;
	if (!a)
		return (!printf("Missing Element\n"));
	return (1);
}

void	print_data(t_components *comp)
{
	int	i;

	i = 0;
	if (comp->elements.n_texture)
		printf("North: %s\n", comp->elements.n_texture);
	if (comp->elements.s_texture)
		printf("South: %s\n", comp->elements.s_texture);
	if (comp->elements.w_texture)
		printf("West: %s\n", comp->elements.w_texture);
	if (comp->elements.e_texture)
		printf("East: %s\n", comp->elements.e_texture);
	if (comp->elements.f_color)
		printf("Floor Color %d\n", comp->elements.f_color);
	if (comp->elements.c_color)
		printf("Ceil Color %d\n", comp->elements.c_color);
	printf("X: %d\n", comp->player_x);
	printf("Y: %d\n", comp->player_y);
	if (comp->map)
	{
		printf("\n-------------------------\n\n");
		while (comp->map[i])
			printf("%s\n", comp->map[i++]);
	}
	printf("map width: %d\n", comp->map_w);
	printf("map height: %d\n", comp->map_h);
}

int	main(int argc, char *argv[])
{
	t_components	comp;

	if (argc != 2)
		return (printf(YEL "Usage: ./cub3d map.cub \n" RESET));
	initialize_comps(&comp);
	if (!read_file(argv[1], &comp) || !check_comps(&comp))
		return (0);
	set_player_cords(&comp);
	print_data(&comp);
}
