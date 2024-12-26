#include "../include/my.h"

static void init_struct(t_data *data)
{
    data->fd = 0;
    data->size_mmap = 0;
    data->file_data = NULL;
}

static void error_handling(int argc, char **argv, t_data *data)
{
    if (argc != 2)
        exit(1);
    if ((data->fd = open(argv[1], O_RDONLY)) == -1)
        exit(1);
}

static void init_mmap(t_data *data, char *file)
{
    struct stat s;

    if (fstat(data->fd, &s) == -1)
        exit(1);
    if (S_ISDIR(s.st_mode))
        exit(1);
    data->file_data = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, data->fd, 0);
    data->size_mmap = s.st_size;
}

int main(int argc, char **argv)
{
    t_data data;

    init_struct(&data);
    error_handling(argc, argv, &data);
    init_mmap(&data, argv[1]);
    printf("%s\n", data.file_data);
    return 0;
}