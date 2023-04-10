/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:27:37 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/04/09 18:28:21 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_dir(t_elements *elements)
{
	int	*fds;
	int	i;

	fds = malloc(4 * sizeof(int));
	fds[0] = open(elements->e_texture, O_DIRECTORY);
	fds[1] = open(elements->n_texture, O_DIRECTORY);
	fds[2] = open(elements->s_texture, O_DIRECTORY);
	fds[3] = open(elements->w_texture, O_DIRECTORY);
	i = 4;
	while (--i >= 0)
	{
		if (fds[i] != -1)
			return (free(fds), 1);
	}
	return (free(fds), 0);
}
