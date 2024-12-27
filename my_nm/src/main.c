/*
** EPITECH PROJECT, 2024
** my_nm
** File description:
** main
*/

#include "../include/my.h"

static void error_handling(int argc, char **argv, t_data *data)
{
    if (argc != 2)
        exit(1);
    if ((data->fd = open(argv[1], O_RDONLY)) == -1)
        exit(1);
    return;
}

static void choose_bits(t_data *data, char *file)
{
    Elf64_Ehdr *elf = (Elf64_Ehdr *)data->file_data;

    if (elf->e_ident[EI_CLASS] == ELFCLASS32)
        exit(1);
    if (elf->e_ident[EI_CLASS] == ELFCLASS64) {
        init_data(&data);
        new_version(&data, file);
    }
    return;
}

int main(int argc, char **argv)
{
    t_data data;

    init_struct(&data);
    error_handling(argc, argv, &data);
    init_mmap(&data, argv[1]);
    choose_bits(&data, argv[1]);
    return 0;
}
