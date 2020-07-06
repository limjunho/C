#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void main(void)
{
	char buf[100];
	int fd = open("/proc/wireless", O_RDWR);
	read(fd, buf, 100);
	printf("%s",buf);
}	
  