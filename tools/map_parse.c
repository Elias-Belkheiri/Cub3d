/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:03:31 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/04/09 18:07:13 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	dup_map(t_components *comp)
{
	int		max;
	int		i;
	char	**dup_map;

	max = get_max_line(comp->map) + 2;
	comp->map_w = max;
	dup_map = malloc((arr_size(comp->map) + 3) * sizeof(char *));
	dup_map[arr_size(comp->map) + 2] = 0;
	dup_map[0] = fill_map(max, NULL);
	dup_map[arr_size(comp->map) + 1] = fill_map(max, NULL);
	i = 0;
	while (comp->map[i])
	{
		dup_map[i + 1] = fill_map(max, comp->map[i]);
		i++;
	}
	comp->map_h = i + 2;
	ft_free_all_mfs(comp->map);
	comp->map = dup_map;
	return (check_walls(dup_map));
}

int	read_map(int fd, t_components *comp, char *line)
{
	char	*tmp;
	char	*map;

	tmp = line;
	map = NULL;
	while (tmp)
	{
		if (tmp && *tmp == '\n')
			return (free(tmp), free(map), !printf("Invalid Map\n"));
		map = ft_join(map, tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	comp->map = ft_split(map, '\n');
	free(map);
	return (1);
}

int	valid_space(char **map, t_components *comp)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
			{
				if (!check_space(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (dup_map(comp));
}

int	check_map(char **map, t_components *comp)
{
	int	player;
	int	i;
	int	j;

	player = 0;
	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'W' || map[i][j] == 'E')
			{
				if (player)
					return (!printf("Too many players\n"));
				player = 1;
			}
			else if (map[i][j] != '1' && map[i][j] != '0' &&
				map[i][j] != ' ' && map[i][j] != 'D')
				return (!printf("Invalid character in map \n"));
			j++;
		}
	}
	return (check_map_2(map, comp, player));
}

int	is_map_element(char *str)
{
	int	i;

	i = 0;
	while ((str[i] && str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] && (str[i] == '1' || str[i] == '0'))
		return (1);
	return (0);
}
