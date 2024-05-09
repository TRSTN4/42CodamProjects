#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int fd;
	char *buffer;
	int i;

	fd = open("./numbers.txt", O_RDWR);
	
	i = 0;
	if (buffer != 0)
	{
		while(buffer[i] != '\n')
		{
			read(fd, &buffer[i], 1);
			write(1, &buffer[i], 1);
			i++;
		}
		printf("test:  %s", &buffer[i]);
	}
	free(buffer);
}
