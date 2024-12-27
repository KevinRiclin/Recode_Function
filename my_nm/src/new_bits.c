/*
** EPITECH PROJECT, 2024
** my_nm
** File description:
** new_bits
*/

#include "../include/my.h"

static Elf64_Shdr *find_section(t_data *data, char *name)
{
    for (int i = 0; i < data->section_count; i++)
        if (strcmp(&data->section_names[data->sections[i].sh_name], name) == 0)
            return (&data->sections[i]);
    return (NULL);
}

static char *get_symbol_type(uint8_t type)
{
    if (type == STT_NOTYPE)
        return ("STT_NOTYPE");
    if (type == STT_OBJECT)
        return ("STT_OBJECT");
    if (type == STT_FUNC)
        return ("STT_FUNC");
    if (type == STT_SECTION)
        return ("STT_SECTION");
    if (type == STT_FILE)
        return ("STT_FILE");
    return ("STT_UNKNOWN");
}

static char *get_symbol_bind(uint8_t bind)
{
    if (bind == STB_LOCAL)
        return ("STB_LOCAL");
    if (bind == STB_GLOBAL)
        return ("STB_GLOBAL");
    if (bind == STB_WEAK)
        return ("STB_WEAK");
    return ("STB_UNKNOWN");
}

static char *get_symbol_visibility(uint8_t visibility)
{
    if (visibility == STV_DEFAULT)
        return ("STV_DEFAULT");
    if (visibility == STV_INTERNAL)
        return ("STV_INTERNAL");
    if (visibility == STV_HIDDEN)
        return ("STV_HIDDEN");
    if (visibility == STV_PROTECTED)
        return ("STV_PROTECTED");
    return ("STV_UNKNOWN");
}

static char *get_section_name(Elf64_Sym *sym, t_data *data)
{
    if (sym->st_shndx == SHN_UNDEF)
        return ("UND");
    if (sym->st_shndx == SHN_ABS)
        return ("ABS");
    if (sym->st_shndx < data->section_count)
        return &data->section_names[data->sections[sym->st_shndx].sh_name];
    return ("UNKNOWN");
}

static void print_symbol_info(Elf64_Sym *sym, t_data *data)
{
    printf("%016lx ", sym->st_value);
    printf("%ld ", sym->st_size);
    printf("%s ", get_symbol_type(ELF64_ST_TYPE(sym->st_info)));
    printf("%s ", get_symbol_bind(ELF64_ST_BIND(sym->st_info)));
    printf("%s ", get_symbol_visibility(ELF64_ST_VISIBILITY(sym->st_other)));
    printf("%s ", get_section_name(sym, data));
    printf("%s\n", &data->symbol_names[sym->st_name]);
    return;
}

static void process_symbols(Elf64_Shdr *symtab, t_data *data)
{
    Elf64_Sym *symbols = (Elf64_Sym *)(data->file_data + symtab->sh_offset);
    int num_symbols = symtab->sh_size / symtab->sh_entsize;

    for (int i = 0; i < num_symbols; i++)
        print_symbol_info(&symbols[i], data);
    return;
}

void new_version(t_data *data, char *file)
{
    Elf64_Shdr *symtab = find_section(data, ".symtab");
    Elf64_Shdr *strtab = find_section(data, ".strtab");

    data->symbol_names = (char *)(data->file_data + strtab->sh_offset);
    process_symbols(symtab, data);
    return;
}
