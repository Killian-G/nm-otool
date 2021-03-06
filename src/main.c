/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:52:40 by kguibout          #+#    #+#             */
/*   Updated: 2021/10/08 16:28:37 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int	open_file(char *path, int flags)
{
	int			fd;

	fd = open(path, flags);
	if (fd == -1)
	{
		ft_printf("%s: '%s': %s\n", get_env()->exec_name, get_env()->path,
				  strerror(errno));
		return (-1);
	}
	return (fd);
}

void	print_elf_header_magic(Elf64_Ehdr *header)
{
	ft_printf("Magic number: %#x '%c' '%c' '%c'\n", header->e_ident[EI_MAG0],
			  header->e_ident[EI_MAG1], header->e_ident[EI_MAG2],
			  header->e_ident[EI_MAG3]);
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
	if (index >= get_env()->symbol_sting_table_size)
		return (NULL);
	return (get_env()->symbol_sting_table + index);
}

Elf64_Shdr  *get_section_header_64bit(size_t index)
{
    Elf64_Shdr	*section_header;

    if (index >= ((Elf64_Ehdr *)get_env()->elf_file)->e_shnum)
        return (NULL);
    section_header = get_env()->elf_file + ((Elf64_Ehdr *)get_env()->elf_file)->e_shoff;
    section_header += index;
    return (section_header);
}

Elf32_Shdr  *get_section_header_32bit(size_t index)
{
	Elf32_Shdr	*section_header;

	if (index >= ((Elf32_Ehdr *)get_env()->elf_file)->e_shnum)
		return (NULL);
	section_header = get_env()->elf_file + ((Elf32_Ehdr *)get_env()->elf_file)->e_shoff;
	section_header += index;
	return (section_header);
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

Elf64_Shdr	*get_string_table_section_header_64bit()
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

Elf32_Shdr	*get_string_table_section_header_32bit()
{
	Elf32_Ehdr	*header;
	Elf32_Shdr	*section_array;
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

bool get_string_tables_64bit(Elf64_Ehdr *header)
{
	Elf64_Shdr	*section_header;

	section_header = get_env()->elf_file + header->e_shoff;
	section_header += header->e_shstrndx;
	get_env()->section_sting_table = get_env()->elf_file + section_header->sh_offset;
	get_env()->section_sting_table_size = section_header->sh_size;
	section_header = get_string_table_section_header_64bit();
	if (section_header == NULL)
	{
		ft_printf("%s: %s: no symbols\n", get_env()->exec_name, get_env()->path);
		return (false);
	}
	get_env()->symbol_sting_table = get_env()->elf_file + section_header->sh_offset;
	get_env()->symbol_sting_table_size = section_header->sh_size;
	return (true);
}

bool get_string_tables_32bit(Elf32_Ehdr *header)
{
	Elf32_Shdr	*section_header;

	section_header = get_env()->elf_file + header->e_shoff;
	section_header += header->e_shstrndx;
	get_env()->section_sting_table = get_env()->elf_file + section_header->sh_offset;
	get_env()->section_sting_table_size = section_header->sh_size;
	section_header = get_string_table_section_header_32bit();
	if (section_header == NULL)
	{
		ft_printf("%s: %s: no symbols\n", get_env()->exec_name, get_env()->path);
		return (false);
	}
	get_env()->symbol_sting_table = get_env()->elf_file + section_header->sh_offset;
	get_env()->symbol_sting_table_size = section_header->sh_size;
	return (true);
}

bool init_elf_data(void	*elf_file)
{
	Elf32_Ehdr	*header;

	if (get_env()->files.total > 1)
		ft_printf("\n%s:\n", get_env()->path);
	get_env()->elf_file = elf_file;
	header = elf_file;
	if (header->e_ident[EI_CLASS] == ELFCLASS64)
		get_env()->is_64bit = true;
	else if (header->e_ident[EI_CLASS] == ELFCLASS32)
		get_env()->is_64bit = false;
	else
	{
		// TODO Check behaviour of nm for invalid class
		ft_printf("Invalid class %d\n", header->e_ident[EI_CLASS]);
		return (false);
	}
	if (get_env()->is_64bit)
		return (get_string_tables_64bit((Elf64_Ehdr *)header));
	else
		return (get_string_tables_32bit((Elf32_Ehdr *)header));
}

int	get_file_descriptor()
{
	int 	fd;
	char	*path;

	if (get_env()->files.total == 0)
		get_env()->path = "a.out";
	else
	{
		path = *(char **)vector_get(&get_env()->files, get_env()->file_index++);
		get_env()->path = path;
	}
	fd = open_file(get_env()->path, O_RDONLY);
	return (fd);
}

void	print_error(const char *error_message)
{
	ft_printf("%s: %s: %s\n", get_env()->exec_name, get_env()->path, error_message);
}

t_file_data	get_file_data()
{
	int			fd;
	struct stat	buff;
	void		*mem;

	fd = get_file_descriptor();
	if (fd == -1)
		return ((t_file_data){0});
	fstat(fd, &buff);
	if ((buff.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_dprintf(2,"%s: Warning: '%s' is a directory\n", get_env()->exec_name, get_env()->path);
		close(fd);
		return ((t_file_data){0});
	}
	mem = mmap(NULL, buff.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);
	if (mem == MAP_FAILED)
	{
		print_error("Fail to allocate file data");
		return ((t_file_data){0});
	}
	return ((t_file_data){.data=mem, .length=buff.st_size});
}

// TODO Check for test, test_, test__

void Add()
{

}

void tndd()
{

}

int	custom_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	size_t			j;
	unsigned char	*s1_tmp;
	unsigned char	*s2_tmp;

	s1_tmp = (unsigned char *)s1;
	s2_tmp = (unsigned char *)s2;
	i = 0;
	j = 0;
	while (true)
	{
		if (s1_tmp[i] == '\0' || s2_tmp[j] == '\0')
			break;
		if (!ft_isalnum(s1_tmp[i]))
		{
			i++;
			continue;
		}
		if (!ft_isalnum(s2_tmp[j]))
		{
			j++;
			continue;
		}
		if (ft_tolower(s1_tmp[i]) != ft_tolower(s2_tmp[j]))
			break;
		i++;
		j++;
	}
	if (s1_tmp[i] == s2_tmp[j])
	{
		return ((int)(j - i));
	}
	return ((int)(ft_tolower(s1_tmp[i]) - ft_tolower(s2_tmp[j])));
}

int sym_cmp(void *d1, void *d2)
{
	Elf64_Sym *tmp1;
	Elf64_Sym *tmp2;

	tmp1 = *(Elf64_Sym **)d1;
	tmp2 = *(Elf64_Sym **)d2;
	return (custom_strcmp(get_string_from_shstrtab(tmp1->st_name), get_string_from_shstrtab(tmp2->st_name)));
}

bool    insert_symbol_in_alphabetical_order_64bit(t_vector *vector, Elf64_Sym *symbol, bool reverse_order)
{
    size_t j = 0;

    while (j < vector->total)
    {
        Elf64_Sym *tmp_symbol;
        tmp_symbol = *(Elf64_Sym **)vector_get(vector, j);
        if ((custom_strcmp(get_string_from_shstrtab(symbol->st_name), get_string_from_shstrtab(tmp_symbol->st_name)) < 0) != reverse_order)
        {
            if (!vector_insert(vector, j, &symbol))
                return (false);
            break;
        }
        j++;
    }
    if (j == vector->total)
    {
        if (!vector_push(vector, &symbol))
            return (false);
    }
    return (true);
}

bool    insert_symbol_in_alphabetical_order_32bit(t_vector *vector, Elf32_Sym *symbol, bool reverse_order)
{
	size_t j = 0;

	while (j < vector->total)
	{
		Elf32_Sym *tmp_symbol;
		tmp_symbol = *(Elf32_Sym **)vector_get(vector, j);
		if ((custom_strcmp(get_string_from_shstrtab(symbol->st_name), get_string_from_shstrtab(tmp_symbol->st_name)) < 0) != reverse_order)
		{
			if (!vector_insert(vector, j, &symbol))
				return (false);
			break;
		}
		j++;
	}
	if (j == vector->total)
	{
		if (!vector_push(vector, &symbol))
			return (false);
	}
	return (true);
}

char get_right_symbol(unsigned char binding, char local, char global)
{
	if (binding == STB_LOCAL)
		return (local);
	else
		return (global);
}

unsigned char	get_binding(void	*sym)
{
	if (get_env()->is_64bit)
		return (ELF64_ST_BIND(((Elf64_Sym *)sym)->st_info));
	else
		return (ELF32_ST_BIND(((Elf32_Sym *)sym)->st_info));
}

void	*get_section_header(void *sym)
{
	if (get_env()->is_64bit)
		return (get_section_header_64bit(((Elf64_Sym *)sym)->st_shndx));
	else
		return (get_section_header_32bit(((Elf32_Sym *)sym)->st_shndx));
}

unsigned char get_symbol_type(void *sym)
{
	if (get_env()->is_64bit)
		return (ELF64_ST_TYPE(((Elf64_Sym *)sym)->st_info));
	else
		return (ELF32_ST_TYPE(((Elf32_Sym *)sym)->st_info));
}

Elf64_Addr get_symbol_value(void *sym)
{
	if (get_env()->is_64bit)
		return (((Elf64_Sym *)sym)->st_value);
	else
		return (((Elf32_Sym *)sym)->st_value);
}

Elf64_Section	get_symbol_section_index(void *sym)
{
	if (get_env()->is_64bit)
		return (((Elf64_Sym *)sym)->st_shndx);
	else
		return (((Elf32_Sym *)sym)->st_shndx);
}

Elf64_Word	get_section_header_type(void *section_header)
{
	if (get_env()->is_64bit)
		return (((Elf64_Shdr *)section_header)->sh_type);
	else
		return (((Elf32_Shdr *)section_header)->sh_type);
}

Elf64_Xword	get_section_header_flags(void *section_header)
{
	if (get_env()->is_64bit)
		return (((Elf64_Shdr *)section_header)->sh_flags);
	else
		return (((Elf32_Shdr *)section_header)->sh_flags);
}

char	weak_symbol(void *sym)
{
	if (get_symbol_type(sym) == STT_OBJECT)
	{
		if (get_symbol_value(sym) == 0)
			return 'v';
		else
			return 'V';
	}
	else
	{
		if (get_symbol_value(sym) == 0)
			return 'w';
		else
			return 'W';
	}
}

char get_symbol_type_char(void *sym)
{
	unsigned char	binding;
	void			*section_header;

	section_header = get_section_header(sym);
	if (section_header == NULL)
		return (0);
	binding = get_binding(sym);
	if (binding >= STB_NUM)
	{
		ft_printf("Symbol binding is invalid or not supported (%hhd)",
				  binding);
		return (0);
	}
	if (binding == STB_WEAK)
		return weak_symbol(sym);
	else if (get_symbol_section_index(sym) == SHN_UNDEF)
		return 'U';
	else if (get_section_header_type(section_header) == SHT_NOBITS)
		return (get_right_symbol(binding, 'b', 'B'));
	else if (get_section_header_flags(section_header) & SHF_ALLOC)
	{
		if (get_section_header_flags(section_header) & SHF_EXECINSTR)
			return (get_right_symbol(binding, 't', 'T'));
		else if (!(get_section_header_flags(section_header) & SHF_WRITE))
			return (get_right_symbol(binding, 'r', 'R'));
		return (get_right_symbol(binding, 'd', 'D'));
	}
	else
		return '?';
}

//char get_symbol_type_char_64bit(Elf64_Sym *sym)
//{
//	Elf64_Shdr		*section_header;
//	unsigned char	binding;
//
//	section_header = get_section_header_64bit(sym->st_shndx);
//	if (section_header == NULL)
//		return (0);
//	binding = ELF64_ST_BIND(sym->st_info);
//	if (binding >= STB_NUM)
//	{
//		ft_printf("Symbol binding is invalid or not supported (%hhd)", binding);
//		return (0);
//	}
//	// TODO Check for STB_WEAK and for STB_LOPROC, STB_HIPROC
//	if (binding == STB_WEAK)
//	{
//		if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
//		{
//			if (sym->st_value == 0)
//				return 'v';
//			else
//				return 'V';
//		}
//		else
//		{
//			if (sym->st_value == 0)
//				return 'w';
//			else
//				return 'W';
//		}
//	}
//	else if (sym->st_shndx == SHN_UNDEF)
//		return 'U';
//	else if (section_header->sh_type == SHT_NOBITS)
//		return (get_right_symbol(binding, 'b', 'B'));
//	else if (section_header->sh_flags & SHF_ALLOC)
//	{
//		if (section_header->sh_flags & SHF_EXECINSTR)
//			return (get_right_symbol(binding, 't', 'T'));
//		else if (!(section_header->sh_flags & SHF_WRITE))
//			return (get_right_symbol(binding, 'r', 'R'));
//		return (get_right_symbol(binding, 'd', 'D'));
//	}
//	else
//		return '?';
//}
//
//char get_symbol_type_char_32bit(Elf32_Sym *sym)
//{
//	Elf32_Shdr		*section_header;
//	unsigned char	binding;
//
//	section_header = get_section_header_32bit(sym->st_shndx);
//	if (section_header == NULL)
//		return (0);
//	binding = ELF32_ST_BIND(sym->st_info);
//	if (binding >= STB_NUM)
//	{
//		ft_printf("Symbol binding is invalid or not supported (%hhd)", binding);
//		return (0);
//	}
//	// TODO Check for STB_WEAK and for STB_LOPROC, STB_HIPROC
//	if (binding == STB_WEAK)
//	{
//		if (ELF32_ST_TYPE(sym->st_info) == STT_OBJECT)
//		{
//			if (sym->st_value == 0)
//				return 'v';
//			else
//				return 'V';
//		}
//		else
//		{
//			if (sym->st_value == 0)
//				return 'w';
//			else
//				return 'W';
//		}
//	}
//	else if (sym->st_shndx == SHN_UNDEF)
//		return 'U';
//	else if (section_header->sh_type == SHT_NOBITS)
//		return (get_right_symbol(binding, 'b', 'B'));
//	else if (section_header->sh_flags & SHF_ALLOC)
//	{
//		if (section_header->sh_flags & SHF_EXECINSTR)
//			return (get_right_symbol(binding, 't', 'T'));
//		else if (!(section_header->sh_flags & SHF_WRITE))
//			return (get_right_symbol(binding, 'r', 'R'));
//		return (get_right_symbol(binding, 'd', 'D'));
//	}
//	else
//		return '?';
//}

//int test()
//{
//	return 3;
//}
//
//int tea_t()
//{
//	return 3;
//}
//
//int te_st()
//{
//	return 3;
//}

// TODO Check for 'B'
/**
 * @warning Do not free the returned string !
 * @brief
 * @param sym
 * @return
 */
char	*get_right_address_string(Elf64_Addr address, char sym_char)
{
	static char	buff[17];

	if (address != 0 || sym_char == 'b' || sym_char == 'B')
	{
		ft_snprintf(buff, sizeof(buff), "%016x", address);
		return (buff);
	}
	else
		return ("                ");
}

t_vector	*init_symbols_vector_64bit(void)
{
	t_vector	*symbols;

	symbols = malloc(sizeof(t_vector));
	if (symbols == NULL)
		return (NULL);
	if (!vector_init(symbols, sizeof(Elf64_Sym *)))
	{
		free(symbols);
		return (NULL);
	}
	return (symbols);
}

t_vector	*get_all_symbol_64bit(void)
{
	Elf64_Sym	*symbol_array;
	t_vector	*vector;
	Elf64_Sym	*sym;
	size_t		i;

	vector = init_symbols_vector_64bit();
	if (vector == NULL)
		return (NULL);
	symbol_array = get_env()->elf_file
		+ get_symbol_table_section_header()->sh_offset;
	i = 0;
	while (i < get_symbol_table_section_header()->sh_size
		/ get_symbol_table_section_header()->sh_entsize)
	{
		if (symbol_array[i].st_name != 0
			&& ELF64_ST_TYPE(symbol_array[i].st_info) != STT_FILE)
		{
			sym = &symbol_array[i];
			vector_push(vector, &sym);
		}
		i++;
	}
	return (vector);
}

t_vector	*init_symbols_vector_32bit(void)
{
	t_vector	*symbols;

	symbols = malloc(sizeof(t_vector));
	if (symbols == NULL)
		return (NULL);
	if (!vector_init(symbols, sizeof(Elf32_Sym *)))
	{
		free(symbols);
		return (NULL);
	}
	return (symbols);
}

t_vector	*get_all_symbol_32bit(void)
{
	Elf32_Sym	*symbol_array;
	t_vector	*symbols;
	Elf32_Sym	*sym;
	size_t		i;

	symbols = init_symbols_vector_32bit();
	if (symbols == NULL)
		return (NULL);
	symbol_array = get_env()->elf_file
		+ get_symbol_table_section_header()->sh_offset;
	i = 0;
	while (i < get_symbol_table_section_header()->sh_size
		/ get_symbol_table_section_header()->sh_entsize)
	{
		if (symbol_array[i].st_name != 0
			&& ELF64_ST_TYPE(symbol_array[i].st_info) != STT_FILE)
		{
			sym = &symbol_array[i];
			vector_push(symbols, &sym);
		}
		i++;
	}
	return (symbols);
}
//insert_symbol_in_alphabetical_order_32bit(vector, &symbol_array[i],
// get_env()->options.reverse);

void	print_debug_info_64bit(Elf64_Sym *sym)
{
	char	*bind;

	if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
		bind = "LOCAL";
	else
		bind = "EXTERNAL";
	ft_printf(" | binding: %s | section: %s",
		bind,
		get_section_string_from_strtab(get_section_header_64bit(
				sym->st_shndx)->sh_name));
}

bool	print_symbols_64bit(t_vector *vector)
{
	size_t		i;
	char		symbol_char;
	Elf64_Sym	*sym;

	i = 0;
	while (i < vector->total)
	{
		sym = *(Elf64_Sym **)vector_get(vector, i);
		symbol_char = get_symbol_type_char(sym);
		ft_printf("%s %c %s",
			get_right_address_string(sym->st_value, symbol_char),
			symbol_char,
			get_string_from_shstrtab(sym->st_name));
		if (symbol_char == '?')
			print_debug_info_64bit(sym);
		ft_printf("\n");
		if (symbol_char == '?')
			print_section(get_section_header_64bit(sym->st_shndx));
		i++;
	}
	return (true);
}

void	print_debug_info_32bit(Elf32_Sym *sym)
{
	char	*bind;

	if (ELF32_ST_BIND(sym->st_info) == STB_LOCAL)
		bind = "LOCAL";
	else
		bind = "EXTERNAL";
	ft_printf(" | binding: %s | section: %s",
		bind,
		get_section_string_from_strtab(get_section_header_32bit(
				sym->st_shndx)->sh_name));
}

bool	print_symbols_32bit(t_vector *vector)
{
	size_t		i;
	char		symbol_char;
	Elf32_Sym	*sym;

	i = 0;
	while (i < vector->total)
	{
		sym = *(Elf32_Sym **)vector_get(vector, i);
		symbol_char = get_symbol_type_char(sym);
		ft_printf("%s %c %s",
			get_right_address_string(sym->st_value, symbol_char),
			symbol_char,
			get_string_from_shstrtab(sym->st_name));
		if (symbol_char == '?')
			print_debug_info_32bit(sym);
		ft_printf("\n");
		if (symbol_char == '?')
			print_section(get_section_header_64bit(sym->st_shndx));
		i++;
	}
	return (true);
}

bool	error_free(t_file_data *file_data)
{
	munmap(file_data->data, file_data->length);
	free_env();
	return (false);
}

bool	process_elf_64bit(t_file_data *file_data)
{
	t_vector	*symbols;

	symbols = get_all_symbol_64bit();
	if (symbols == NULL)
		return (error_free(file_data));
	merge_sort(symbols->items, symbols->total, symbols->sizeof_elem, sym_cmp);
	print_symbols_64bit(symbols);
	vector_free(symbols);
	free(symbols);
	return (true);
}

bool	process_elf_32bit(t_file_data *file_data)
{
	t_vector	*symbols;

	symbols = get_all_symbol_32bit();
	if (symbols == NULL)
		return (error_free(file_data));
	print_symbols_32bit(symbols);
	vector_free(symbols);
	free(symbols);
	return (true);
}

int	process_file(void)
{
	t_file_data	file_data;

	file_data = get_file_data();
	if (file_data.data == NULL)
		return (1);
	if (!init_elf_data(file_data.data))
		return (1);
	if (get_env()->is_64bit)
	{
		if (!process_elf_64bit(&file_data))
			return (-1);
	}
	else
	{
		if (!process_elf_32bit(&file_data))
			return (-1);
	}
	munmap(file_data.data, file_data.length);
	if (get_env()->file_index == get_env()->files.total)
		return (0);
	return (1);
}

void printArray(char *A[], int size)
{
	int i;
	for (i=0; i < size; i++)
		ft_printf("%s ", A[i]);
	ft_printf("\n");
}

int	main(int ac, char **av)
{

//	char *arr[] = {"abbbb", "aaa", "q_ggg", "dyyyy", "Ccc__c", "dfddd__",
//				   "___bbbb", "kaaa", "ggg", "_yyyy", "gcCcc", "dddd",
//				   "bbbb", "aaa", "j_ggg", "yyyy", "Ccc__c", "dddd__",
//				   "a___bbbb", "aaa", "ggg", "lf_yyyy", "cCcc", "dddd",
//				   "bbbb", "aaa", "_ggg", "yyyy", "Ccc__c", "dddd__",
//				   "___bbbb", "aaa", "ggg", "_yyyy", "cCcc", "dddd"};
//	int n = sizeof(arr)/sizeof(arr[0]);
//
//	ft_printf("Given array is \n");
//	printArray(arr, n);
//
//	merge_sort_string(arr, n, custom_strcmp);
//
//	ft_printf("\nSorted array is \n");
//	printArray(arr, n);
//	return 0;

	int	ret;

	init_env();
	get_env()->exec_name = av[0];
	if (!parse_args(ac, av))
	{
		free_env();
		return (EXIT_FAILURE);
	}
	while (get_env()->file_index != get_env()->files.total
		|| get_env()->files.total == 0)
	{
		ret = process_file();
		if (ret == 1)
			continue ;
		else if (ret == 0)
			break ;
		else
			return (EXIT_FAILURE);
	}
	free_env();
	return (EXIT_SUCCESS);
}
