/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hflohil- <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 12:39:54 by hflohil-      #+#    #+#                 */
/*   Updated: 2022/08/31 12:39:55 by hflohil-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
int 	index;
int		y_len;
char 	filler;
char	obstacle;
char	square_fill;

y_len = buffer[0];
filler = buffer[1];
obstacle = buffer[2];
square_fill = buffer[3];
*/

//adds the values from the buffer, and appends characters to multimensional array.
void	build_array(char *map_str)
{
//***todo*** MALLOC 2D ARRAY PTR
	char	map_array[100][100];
	int		index_x;
	int		index_y;
	int		i;

	index_y = 0;
	index_x = 0;
	i = 5;
	while (map_str[i] != '\0')
	{
		while (map_str[i] != '\n')
		{
			map_array[index_y][index_x] = map_str[i];
			write(1, &map_array[index_y][index_x], 1);
			index_x++;
			i++;
		}
		write(1, "\n", 1);
		index_y++;
		index_x = 0;
		i++;
	}
}

//measures total size of file and then calculates line length.
void	load_buffer(char *buffer, int fd)
{
	int 	index;
	char	*map_str;

	map_str = malloc(1000);
	index = 0;
	while (index <= 1000)
	{
		map_str[index] = buffer[index];
		index++;
	}
	free(buffer);
	build_array(map_str);
}

//main function, takes .txt, reads and loads it to FD and buffer. Buffer is malloced with 1000 bytes.
//**note** potentially add size_of implemntation for memory efficiency.
int	main(int argc, char *argv[])
{
	char *buffer;
	int fd;

	if (argc == 2)
	{
		buffer = malloc(1000);
		if (buffer == NULL)
			write(1, "Memory not Available", 21);
		else
		{
			fd = open(argv[1], O_RDONLY);
			read(fd, buffer, 1000);
			load_buffer(buffer, fd);
		}
	}
	else
		write(1, "Arguments Error", 16);

	return (0);	
}