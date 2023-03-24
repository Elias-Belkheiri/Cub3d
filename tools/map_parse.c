/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:03:31 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/24 23:10:51 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int get_max_line(char **map)
{
	size_t i;
	int j;

	i = 0;
	j = 0;
	while (map[j])
	{
		if (ft_strlen(map[j]) > i)
			i = ft_strlen(map[j]);
		j++;
	}
	return (i);
}

char *fill_map(int n, char *line)
{
	char *str;
	int i;

	str = malloc(n + 1);
	str[n] = 0;
	str[n - 1] = 'x';
	str[0] = 'x';
	i = 0;
	if (line)
	{
		while (line[++i - 1])
			str[i] = line[i - 1];
		i--;
	}
	while (++i < n)
		str[i] = 'x';
	return (str);
}

int check_walls(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'x' && !check_space(map, i, j))
				return (ft_free_all_mfs(map), 0);
			j++;
		}
		i++;
	}
	return (ft_free_all_mfs(map), 1);
}

int	dup_map(char **map)
{
	int max;
	int i;
	char **dup_map;

	max = get_max_line(map) + 2;
	dup_map = malloc((arr_size(map) + 3) * sizeof(char *));
	dup_map[arr_size(map) + 2] = 0;
	dup_map[0] = fill_map(max, NULL);
	dup_map[arr_size(map) + 1] = fill_map(max, NULL);
	i = 0;
	while (map[i])
	{
		dup_map[i + 1] = fill_map(max, map[i]);
		i++;
	}
	// i = -1;
	// while (dup_map[++i])
	// 	printf("%s\n", dup_map[i]);
	return (check_walls(dup_map));
}

int read_map(int fd, t_components *comp, char *line)
{
	char *tmp;
	char *map;

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

int is_wall_space(int a)
{
	return (a == ' ' || a == '1' || a == 'x');
}

int check_space(char **map, int i, int j)
{
	if (map[i + 1] && map[i + 1][j] && !is_wall_space(map[i + 1][j]))
		return (!printf("Invalid Space/Wall\n"));
	if (i - 1 >= 0 && map[i - 1][j] && !is_wall_space(map[i - 1][j]))
		return (!printf("Invalid Space/Wall\n"));
	if (map[i][j + 1] && !is_wall_space(map[i][j + 1]))
		return (!printf("Invalid Space/Wall\n"));
	if (j - 1 >= 0 && map[i][j - 1] && !is_wall_space(map[i][j - 1]))
		return (!printf("Invalid Space/Wall\n"));
	return (1);
}

int valid_space(char **map)
{
	int i;
	int j;

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
	return (dup_map(map));
}

int check_map(char **map)
{
	int player;
	int i;
	int j;

	player = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
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
	int i;

	i = 0;
	while ((str[i] && str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] && (str[i] == '1' || str[i] == '0'))
		return (1);
	return (0);
}