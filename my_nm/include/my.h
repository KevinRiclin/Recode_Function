/*
** EPITECH PROJECT, 2024
** my_nm
** File description:
** my
*/

#include <elf.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

typedef struct s_symbol_data {
    char *data;
    char *section_names;
    Elf64_Shdr *sections;
    int section_count;
    char *symbol_names;
} t_symbol_data;

typedef struct s_data {
    int fd;
    off_t size_mmap;
    char *file_data;
    t_symbol_data sym_data;
    char *section_names;
    Elf64_Shdr *sections;
    int section_count;
    char *symbol_names;
} t_data;

void init_struct(t_data *data);
void init_mmap(t_data *data, char *file);
void init_data(t_data *data);
void new_version(t_data *data, char *file);
