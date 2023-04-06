/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:11:07 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/04/06 01:31:44 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

typedef struct t_elements
{
	char			*n_texture;
	char			*s_texture;
	char			*w_texture;
	char			*e_texture;
	int				f_color;
	int				c_color;
} t_elements;

typedef struct t_components
{
	t_elements	elements;
	int			player_x;
	int			player_y;
	int			map_h;
	int			map_w;
	char 		**map;
} t_components;

char		*get_next_line(int fd);
size_t		ft_strlen(const char *s);
char		*ft_join(char *str1, char *str2);
char		*ft_strchr(const char *str, int c);
size_t		get_len(char *str);
int     	ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *ptr);
int			ft_strlcpy(char *dst, const char *src, int dstsize);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_free_all_mfs(char **str);
long long	ft_atoi(const char *str);
char		*ft_strtrim(char const *s1, char const *set);
int			ft_isdigit(int arg);
int			read_file(char *arg, t_components *comp);
int	read_map(int fd, t_components *comp, char *line);
int check_map(char **map, t_components *comp);
int is_map_element(char *str);
int	arr_size(char **arr);
int check_space(char **map, int i, int j);
int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);