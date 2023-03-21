/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:03:31 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/21 14:22:28 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	is_wall_space(int a)
{
	return (a == ' ' || a == '1');
}

int	check_space(char **map, int i, int j)
{
	if (map[i + 1] && map[i + 1][j] && !is_wall_space(map[i + 1][j]))
		return (!printf("Invalid Space\n"));
	if (i - 1 >= 0 && map[i - 1][j] && !is_wall_space(map[i - 1][j]))
		return (!printf("Invalid Space\n"));
	if (map[i][j + 1] && !is_wall_space(map[i][j + 1]))
		return (!printf("Invalid Space\n"));
	if (j - 1 >= 0 && map[i][j - 1] && !is_wall_space(map[i][j - 1]))
		return (!printf("Invalid Space\n"));
	return (1);
}

int	valid_space(char **map)
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
	return (1);
}

int	check_map(char **map)
{
	int	player;
	int	i;
	int	j;

	player = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				{
					if (player)
						return (!printf("Too many players\n"));
					player = 1;
				}
			else if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ')
				return (!printf("Invalid character in map \n"));
			j++;
		}
		i++;
	}
	if (!player)
		return (!printf("The Player is missing\n"));
	return (valid_space(map));
}


int is_map_element(char *str)
{
	int	i;

	i = 0;
	while ((str[i] && str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] && (str[i] == '1' || str[i] == '0'))
		return (1);
	return (0);
}