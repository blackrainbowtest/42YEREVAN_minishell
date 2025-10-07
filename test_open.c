#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	const char *file = "./test_files/infile";
	int fd;
	unsigned char *p = (unsigned char *)file;

	printf("[TEST DEBUG]\n");
	printf("  file ptr = %p\n", (void *)file);
	printf("  file str = \"%s\"\n", file);
	printf("  raw bytes: ");
	for (int i = 0; i < 32 && p[i]; i++)
		printf("%02X ", p[i]);
	printf("\n");

	errno = 0;
	fd = open(file, O_RDONLY);
	printf("  open() → fd=%d, errno=%d (%s)\n", fd, errno, strerror(errno));

	if (fd >= 0)
	{
		char buf[128];
		ssize_t n = read(fd, buf, sizeof(buf) - 1);
		if (n >= 0)
		{
			buf[n] = '\0';
			printf("  read() success, content:\n%s\n", buf);
		}
		else
			perror("  read()");
		close(fd);
	}
	else
		perror("  open() failed");

	return 0;
}
