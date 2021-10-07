/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:32:59 by kguibout          #+#    #+#             */
/*   Updated: 2021/10/03 13:59:54 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int open_file(char *path, int flags)
{
	int			fd;

	fd = open(path, flags);
	if (fd == -1)
	{
		ft_printf("%s: '%s': %s\n", get_env()->exec_name, get_env()->path, strerror(errno));
		return (-1);
	}
	return (fd);
}

void	print_elf_header_magic(Elf64_Ehdr *header)
{
	ft_printf("Magic number: %#x '%c' '%c' '%c'\n", header->e_ident[EI_MAG0], header->e_ident[EI_MAG1],
			  header->e_ident[EI_MAG2], header->e_ident[EI_MAG3]);
}

void	print_elf_header_architecture(Elf64_Ehdr *header)
{
	if (header->e_ident[EI_CLASS] == ELFCLASS32)
		ft_printf("Architecture: 32 Bits\n");
	else if (header->e_ident[EI_CLASS] == ELFCLASS64)
		ft_printf("Architecture: 64 Bits\n");
	else
		ft_printf("Architecture: Invalid\n");
}

void	print_elf_header_endian(Elf64_Ehdr *header)
{
	if (header->e_ident[EI_DATA] == ELFDATA2LSB)
		ft_printf("Endian: Little\n");
	else if (header->e_ident[EI_DATA] == ELFDATA2MSB)
		ft_printf("Endian: Big\n");
	else
		ft_printf("Endian: Invalid\n");
}

void	print_elf_header_version(Elf64_Ehdr *header)
{
	if (header->e_ident[EI_VERSION] == EV_CURRENT)
		ft_printf("Version: Current\n");
	else
		ft_printf("Version: Invalid\n");
}

void	print_elf_header_osabi(Elf64_Ehdr *header)
{
	char	*abi;

	if (header->e_ident[EI_OSABI] == ELFOSABI_HPUX)
		abi = "HP-UX";
	else if (header->e_ident[EI_OSABI] == ELFOSABI_NETBSD)
		abi = "NetBSD";
	else if (header->e_ident[EI_OSABI] == ELFOSABI_LINUX)
		abi = "Linux";
	else if (header->e_ident[EI_OSABI] == ELFOSABI_SOLARIS)
		abi = "Solaris";
	else if (header->e_ident[EI_OSABI] == ELFOSABI_IRIX)
		abi = "IRIX";
	else if (header->e_ident[EI_OSABI] == ELFOSABI_FREEBSD)
		abi = "FreBSD";
	else if (header->e_ident[EI_OSABI] == ELFOSABI_TRU64)
		abi = "TRU64 UNIX";
	else if (header->e_ident[EI_OSABI] == ELFOSABI_ARM)
		abi = "ARM architecture";
	else if (header->e_ident[EI_OSABI] == ELFOSABI_STANDALONE)
		abi = "Stand-alone (embedded)";
	else
		abi = "UNIX System V";
	ft_printf("OS ABI: %s\n", abi);
}

void	print_elf_header_abi_version(Elf64_Ehdr *header)
{
	ft_printf("ABI Version: %d\n", header->e_ident[EI_ABIVERSION]);
}

void	print_elf_header_type(Elf64_Ehdr *header)
{
	char	*type;

	if (header->e_type == ET_REL)
		type = "Relocatable";
	else if (header->e_type == ET_EXEC)
		type = "Executable";
	else if (header->e_type == ET_DYN)
		type = "Shared";
	else if (header->e_type == ET_CORE)
		type = "Core";
	else
		type = "Unknown";
	ft_printf("Type: %s\n", type);
}

void	print_elf_header_machine_architecture(__attribute__((unused))Elf64_Ehdr *header)
{
	// TODO: header->e_machine
	ft_printf("Machine architecture not implemented\n");
}

void	print_elf_header_file_version(Elf64_Ehdr *header)
{
	ft_printf("File version: %u\n", header->e_version);
}

void	print_elf_header_entry(Elf64_Ehdr *header)
{
	ft_printf("Entry point: %p\n", header->e_entry);
}

void	print_elf_header_size(Elf64_Ehdr *header)
{
	ft_printf("ELF Header size: %hu\n", header->e_ehsize);
}

void	print_elf_header_program_header_offset(Elf64_Ehdr *header)
{
	ft_printf("Program offset header: %#x\n", header->e_phoff);
}

void	print_elf_header_section_header_offset(Elf64_Ehdr *header)
{
	ft_printf("Section offset header: %#x\n", header->e_shoff);
}

void	print_elf_header_entry_program_header_size(Elf64_Ehdr *header)
{
	ft_printf("Program header entry size: %hu\n", header->e_phentsize);
}

void	print_elf_header_number_entries_program_header(Elf64_Ehdr *header)
{
	ft_printf("Program header entries number: %hu\n", header->e_phnum);
}

void	print_elf_header_entry_section_header_size(Elf64_Ehdr *header)
{
	ft_printf("Section header entry size: %hu\n", header->e_shentsize);
}

void	print_elf_header_number_entries_section_header(Elf64_Ehdr *header)
{
	ft_printf("Section header entries number: %hu\n", header->e_shnum);
}

void	print_elf_header_string_section_index(Elf64_Ehdr *header)
{
	ft_printf("Section header section index: %hu\n", header->e_shstrndx);
}

//void	print_program_header(Elf64_Ehdr *header)
//{
//
//}

char	*get_section_string_from_strtab(t_u32 index)
{
	if (index >= get_env()->section_sting_table_size)
		return (NULL);
	return (get_env()->section_sting_table + index);
}

char	*get_string_from_shstrtab(t_u32 index)
{
	if (index >= get_env()->sting_table_size)
		return (NULL);
	return (get_env()->sting_table + index);
}

void	print_section_header(size_t	index)
{
	Elf64_Shdr	*section_header;

	if (index >= ((Elf64_Ehdr *)get_env()->elf_file)->e_shnum)
		return;
	section_header = get_env()->elf_file + ((Elf64_Ehdr *)get_env()->elf_file)->e_shoff;
	section_header += index;
	ft_printf("Section %d\n", index);
	ft_printf("Section header name: %s\n", get_section_string_from_strtab(section_header->sh_name));
//	ft_printf("Section header address: %p\n", section_header->sh_addr);
//	ft_printf("Section header offset: %zu\n", section_header->sh_offset);
//	ft_printf("Section header size: %zu\n", section_header->sh_size);
}

void	print_section_string()
{
	Elf64_Shdr	*section_header;
	Elf64_Ehdr	*elf_header;

	elf_header = get_env()->elf_file;
	section_header = get_env()->elf_file + elf_header->e_shoff;
	section_header += elf_header->e_shstrndx;
	ft_printf("Section elf_header name: %s\n", get_section_string_from_strtab(section_header->sh_name));
	ft_printf("Section elf_header address: %p\n", section_header->sh_addr);
	ft_printf("Section elf_header offset: %zu\n", section_header->sh_offset);
	ft_printf("Section elf_header size: %zu\n", section_header->sh_size);
	ft_printf("%s\n", get_section_string_from_strtab(section_header->sh_name));
}

Elf64_Shdr	*get_symbol_table_section_header()
{
	Elf64_Ehdr	*header;
	Elf64_Shdr	*section_array;
	size_t		i;

	header = get_env()->elf_file;
	section_array = get_env()->elf_file + header->e_shoff;
	i = 0;
	while (i < header->e_shnum)
	{
		if (ft_strequ(get_section_string_from_strtab(section_array[i].sh_name), ".symtab"))
			return (&section_array[i]);
		i++;
	}
	return (NULL);
}

Elf64_Shdr	*get_string_table_section_header()
{
	Elf64_Ehdr	*header;
	Elf64_Shdr	*section_array;
	size_t		i;

	header = get_env()->elf_file;
	section_array = get_env()->elf_file + header->e_shoff;
	i = 0;
	while (i < header->e_shnum)
	{
		if (ft_strequ(get_section_string_from_strtab(section_array[i].sh_name), ".strtab"))
			return (&section_array[i]);
		i++;
	}
	return (NULL);
}

size_t 	get_symbol_table_section_header_number()
{
	Elf64_Ehdr	*header;
	Elf64_Shdr	*section_array;
	size_t		i;
	size_t		j;

	j = 0;
	header = get_env()->elf_file;
	section_array = get_env()->elf_file + header->e_shoff;
	i = 0;
	while (i < header->e_shnum)
	{
		if (section_array[i].sh_type == SHT_SYMTAB)
			j++;
		i++;
	}
	return (j);
}

void	print_elf_header_info(Elf64_Ehdr *header)
{
	if (header == NULL)
		return;
	ft_printf("ELF Header Info:\n-----------------------------\n");
	print_elf_header_magic(header);
	print_elf_header_architecture(header);
	print_elf_header_endian(header);
	print_elf_header_version(header);
	print_elf_header_osabi(header);
	print_elf_header_abi_version(header);
	print_elf_header_type(header);
	print_elf_header_machine_architecture(header);
	print_elf_header_file_version(header);
	print_elf_header_entry(header);
	print_elf_header_size(header);
	print_elf_header_program_header_offset(header);
	print_elf_header_section_header_offset(header);
	print_elf_header_entry_program_header_size(header);
	print_elf_header_number_entries_program_header(header);
	print_elf_header_entry_section_header_size(header);
	print_elf_header_number_entries_section_header(header);
	print_elf_header_string_section_index(header);
	size_t	i;

	i = 0;
	while (i < header->e_shnum)
	{
		print_section_header(i);
		i++;
	}
	ft_printf("-----------------------------\n");
}

void init_elf_data(void	*elf_file)
{
	Elf64_Ehdr	*header;
	Elf64_Shdr	*section_header;

	get_env()->elf_file = elf_file;
	header = elf_file;
	section_header = get_env()->elf_file + header->e_shoff;
	section_header += header->e_shstrndx;
	get_env()->section_sting_table = elf_file + section_header->sh_offset;
	get_env()->section_sting_table_size = section_header->sh_size;
	section_header = get_string_table_section_header();
	get_env()->sting_table = elf_file + section_header->sh_offset;
	get_env()->sting_table_size = section_header->sh_size;
}

int	get_file_descriptor(int number_of_args, char **args)
{
	int fd;

	if (number_of_args <= 1)
	{
		get_env()->path = "a.out";
		fd = open_file(get_env()->path, O_RDONLY);
	}
	else
	{
		get_env()->path = args[1];
		fd = open_file(args[1], O_RDONLY);
	}
	return (fd);
}

void	print_error(const char *error_message)
{
	ft_printf("%s: %s: %s\n", get_env()->exec_name, get_env()->path, error_message);
}

void *get_file_data(int number_of_args, char **args)
{
	int			fd;
	struct stat	buff;
	void		*mem;

	fd = get_file_descriptor(number_of_args, args);
	if (fd == -1)
		return (NULL);
	fstat(fd, &buff);
	mem = mmap(NULL, buff.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (mem == NULL)
	{
		print_error("Fail to allocate file data");
		return (NULL);
	}
	return (mem);
}

int main(int ac, char **av)
{
	void *mem;

	get_env()->exec_name = av[0];
	mem = get_file_data(ac, av);
	if (mem == NULL)
		return (EXIT_FAILURE);
	init_elf_data(mem);
	Elf64_Ehdr *elf_header;
	elf_header = mem;
	print_elf_header_info(elf_header);

	Elf64_Sym	*symbol_array;

	symbol_array = get_env()->elf_file + get_symbol_table_section_header()->sh_offset;
	size_t i = 0;
	while (i < get_symbol_table_section_header()->sh_size / get_symbol_table_section_header()->sh_entsize)
	{
		if (symbol_array[i].st_name != 0)
			ft_printf("%s\n", get_string_from_shstrtab(symbol_array[i].st_name));
		i++;
	}
	ft_printf("%zu\n", get_symbol_table_section_header_number());
	return (EXIT_SUCCESS);
}
