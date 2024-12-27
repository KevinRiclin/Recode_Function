/*
** EPITECH PROJECT, 2024
** my_nm
** File description:
** init_struct
*/

#include "../include/my.h"

void init_struct(t_data *data)
{
    data->fd = 0;
    data->size_mmap = 0;
    data->file_data = NULL;
    data->sym_data.data = NULL;
    data->sym_data.section_names = NULL;
    data->sym_data.sections = NULL;
    data->sym_data.section_count = 0;
    data->sym_data.symbol_names = NULL;
}

void init_mmap(t_data *data, char *file)
{
    struct stat s;

    if (fstat(data->fd, &s) == -1)
        exit(1);
    if (S_ISDIR(s.st_mode))
        exit(1);
    data->file_data = mmap(NULL, s.st_size, PROT_READ,
        MAP_PRIVATE, data->fd, 0);
    data->size_mmap = s.st_size;
}

void init_data(t_data *data)
{
    Elf64_Ehdr *elf = (Elf64_Ehdr *)data->file_data;

    data->sections = (Elf64_Shdr *)(data->file_data + elf->e_shoff);
    data->section_names =
        (char *)(data->file_data + data->sections[elf->e_shstrndx].sh_offset);
    data->section_count = elf->e_shnum;
}
