#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define UNFILLED 'r'
#define FILLED 'R'

typedef enum e_enum
{
	IMG_PARAMETERS = 3,
	FIGURE_PARAMETERS = 6,
	INSIDE = 2,
	BORDER = 3,
	OUTSIDE = 4,
}	t_enum;

typedef struct s_img
{
	int		width;
	int		height;
	char	background;
	char	*blueprint;
}	t_img;

typedef struct s_figure
{
	char	type;
	float	x;
	float	y;
	float	width;
	float	height;
	char	c;
}	t_figure;

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_error(char *errormessage)
{
	int	len;

	len = ft_strlen(errormessage);
	write(STDOUT_FILENO, errormessage, len);
	write(STDOUT_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}

void	ft_print_image(t_img img)
{
	int	i;

	i = 0;
	while (i < img.width * img.height)
	{
		write(STDOUT_FILENO, img.blueprint + i, img.width);
		write(STDOUT_FILENO, "\n", 1);
		i += img.width;
	}
}

int	ft_get_parameters(FILE *file, t_img *img)
{
	if ((fscanf(file, "%d %d %c\n", &img->width, &img->height, &img->background)) != IMG_PARAMETERS)
		return (EXIT_FAILURE);
	if (img->width <= 0 || img->width > 300 || img->height <= 0 || img->height > 300)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_get_status(t_figure *rectangle, int x, int y)
{
	if (x < rectangle->x || x > rectangle->x + rectangle->width || y < rectangle->y || y > rectangle->y + rectangle->height)
		return (OUTSIDE);
	if (x - rectangle->x < 1 || rectangle->x + rectangle->width - x < 1 || y - rectangle->y < 1 || rectangle->y + rectangle->height - y < 1)
		return (BORDER);
	return (INSIDE);
}

void	ft_update_blueprint(t_img *img, t_figure *rectangle)
{
	int	x;
	int	y;
	int	status;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			status = ft_get_status(rectangle, x, y);
			if (status == BORDER || (status == INSIDE && rectangle->type == FILLED))
				img->blueprint[x + y * img->width] = rectangle->c;
			x++;
		}
		y++;
	}
}

int	ft_get_figures(FILE *file, t_img *img)
{
	int		ret;
	t_figure rectangle;

	while ((ret = fscanf(file, "%c %f %f %f %f %c\n", &rectangle.type, &rectangle.x, &rectangle.y, &rectangle.width, &rectangle.height, &rectangle.c)) == FIGURE_PARAMETERS)
	{
		if ((rectangle.type != UNFILLED && rectangle.type != FILLED) || rectangle.width <= 0 || rectangle.height <= 0)
			return (EXIT_FAILURE);
		ft_update_blueprint(img, &rectangle);
	}
	if (ret == EOF)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	main (int argc, char **argv)
{
	FILE 	*file;
	t_img	img;
	
	if (argc != 2)
		return (ft_error("Error: argument"));
	if ((file = fopen(argv[1], "r")) == NULL)
		return (ft_error("Error: Operation file corrupted"));
	if (ft_get_parameters(file, &img))
		return (ft_error("Error: Operation file corrupted"));
	img.blueprint = calloc(1, img.height * img.width + 1);
	if (img.blueprint == NULL)
		return (ft_error("Error: Malloc failed"));
	memset(img.blueprint, img.background, img.height * img.width);
	if (ft_get_figures(file, &img))
		return (ft_error("Error: Operation file corrupted"));
	ft_print_image(img);
	return (0);
}