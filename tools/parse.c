/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <elias@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:27:23 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/27 03:42:14 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_player_cords(t_components *comp)
{
	int        i;
    int        j;

    i = 0;
    while (comp->map[i])
    {
        j = 0;
        while (comp->map[i][j])
        {
            if (comp->map[i][j] == 'N' || comp->map[i][j] == 'W'
				|| comp->map[i][j] == 'E' || comp->map[i][j] == 'S')
            {
				comp->player_x = i;
				comp->player_y = j;
				return ;
			}
            j++;
        }
        i++;
    }
}

int	num_of_commas(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			j++;
		if (str[i] != ',' && str[i] != '\n' && !ft_isdigit(str[i]))
			exit(printf("Invalid color\n"));
	}
	return (j);
}

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	parse_rgb(t_elements *elements, char *color, int a)
{
	int				i;
	int				n;
	char			**colors;
	unsigned char	*rgb;

	colors = ft_split(color, ',');
	if (!colors || arr_size(colors) != 3 || num_of_commas(color) != 2)
		return (0);
	i = -1;
	rgb = malloc(3 * sizeof(unsigned char));
	while (colors[++i])
	{
		n = ft_atoi(colors[i]);
		if (n >= 0 && n <= 255)
			rgb[i] = n;
		else
		{
			ft_free_all_mfs(colors);
			return (0);
		}
	}
	if (a)
		elements->c_color = rgb;
	else
		elements->f_color = rgb;
	ft_free_all_mfs(colors);
	return (1);
}

int	check(char **el, t_elements *elements)
{
	if ((arr_size(el) != 2))
		return (!printf("Invalid element \n"));
	if (!ft_strcmp(el[0], "NO"))
		elements->n_texture = ft_strdup(el[1]);
	else if (!ft_strcmp(el[0], "SO"))
		elements->s_texture = ft_strdup(el[1]);
	else if (!ft_strcmp(el[0], "WE"))
		elements->w_texture = ft_strdup(el[1]);
	else if (!ft_strcmp(el[0], "EA"))
		elements->e_texture = ft_strdup(el[1]);
	else if (!ft_strcmp(el[0], "F"))
	{
		if (!parse_rgb(elements, el[1], 0))
			return (!printf("Invalid colors\n"));
	}
	else if (!ft_strcmp(el[0], "C"))
	{
		if (!parse_rgb(elements, el[1], 1))
			return (!printf("Invalid colors\n"));
	}
	else
		return (!printf("Invalid element identifier\n"));
	return (1);
}

int	is_dir(t_elements *elements)
{
	int	*fds;
	int	i;

	fds = malloc(4 * sizeof(int));
	fds[0] = open(elements->e_texture, __O_DIRECTORY);
	fds[1] = open(elements->n_texture, __O_DIRECTORY);
	fds[2] = open(elements->s_texture, __O_DIRECTORY);
	fds[3] = open(elements->w_texture, __O_DIRECTORY);
	i = 4;
	while (--i >= 0)
	{
		if (fds[i] != -1)
			return (free(fds), 1);
	}
	return (free(fds), 0);
}

int	check_element(char *element, t_elements *elements)
{
	char	*tmp;
	char	**el;

	tmp = element;
	if (*tmp != '\n')
	{
		element = ft_strtrim(element, "\n");
		free(tmp);
	}
	if (*element == '\n')
		return (free(element), 1);
	el = ft_split(element, ' ');
	free(element);
	if (!el)
		return (0);
	if (check(el, elements))
		return (ft_free_all_mfs(el), 1);
	return (ft_free_all_mfs(el), 0);
}

int	read_file(char *arg, t_components *comp)
{
	int		scene_file;
	char	*line;

	if (!arg || ft_strlen(arg) < 5
		|| ft_strcmp(arg + ft_strlen(arg) - 4, ".cub"))
		return (0);
	scene_file = open(arg, O_RDONLY);
	if (scene_file == -1)
		return (!printf("Invalid File\n"));
	line = get_next_line(scene_file);
	while (line && !is_map_element(line))
	{
		if (!check_element(line, &comp->elements))
			return (0);
		line = get_next_line(scene_file);
		if (!line)
			break ;
	}
	if (!line || is_dir(&comp->elements))
		return (!printf("Invalid File\n"));
	if (!read_map(scene_file, comp, line))
		return (0);
	set_player_cords(comp);
	return (check_map(comp->map, comp));
}
