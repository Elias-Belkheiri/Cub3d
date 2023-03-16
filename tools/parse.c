/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:27:23 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/16 18:34:31 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// the numbers must be << 255 && > 0


// keep reading until u found a null or a map line;
// for the line that has been read:
// if It's a newline, continue;
// if not, split by space and check the first argument. If it's a valid argument, fill the required variables, if not, print an error and exit;
// for the elements parse, check if there is only two args after spliting. Check if the second arg is valid.

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
	char			*colors;
	unsigned char	*rgb;

	colors = ft_split(color, ',');
	if (!colors || arr_size(colors) != 3)
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
	if (arr_size(el) != 2)
		return (0);
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
			return (0);
	}
	else if (!ft_strcmp(el[0], "C"))
	{
		if (!parse_rgb(elements, el[1], 1))
			return (0);
	}
	else
		return (0);
	return (1);
}

int	check_element(char *element, t_elements *elements)
{
	char	**el;

	if (*element == '\n')
		return (free(element), 1);
	el = ft_split(element, ' ');
	if (!el)
		return (0);
	free(element);
	if (check(el, elements))
		return (ft_free_all_mfs(el), 1);
	return (ft_free_all_mfs(el), 0);
}

int	read_map(char *arg, t_components *comp)
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
	while (line && *line != '0' && *line != '1')
	{
		if (!check_element(line, &comp->elements))
			return (0);
		line = get_next_line(scene_file);
		if (!line)
			break ;
	}
	if (!line)
		return (0);
}