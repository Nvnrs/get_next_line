#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>

int i = 1;

void	test(int fd)
{
	char	*str;

	printf("_________START %d__________\n", i);
	str = get_next_line(fd);
	printf("Output :%s\n\n\n", str);
	free(str);
	i++;
}

int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	test(fd);
	return (0);
}