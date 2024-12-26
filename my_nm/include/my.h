#include <elf.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef struct s_data
{
	int fd;
	off_t size_mmap;
	char *file_data;
} t_data;