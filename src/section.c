#include "ft_nm.h"

void print_type(Elf64_Shdr *section_header)
{
	char	*type = NULL;

	if (section_header->sh_type == SHT_NULL)
		type = "SHT_NULL";
	else if (section_header->sh_type == SHT_PROGBITS)
		type = "SHT_PROGBITS";
	else if (section_header->sh_type == SHT_SYMTAB)
		type = "SHT_SYMTAB";
	else if (section_header->sh_type == SHT_STRTAB)
		type = "SHT_STRTAB";
	else if (section_header->sh_type == SHT_RELA)
		type = "SHT_RELA";
	else if (section_header->sh_type == SHT_HASH)
		type = "SHT_HASH";
	else if (section_header->sh_type == SHT_DYNAMIC)
		type = "SHT_DYNAMIC";
	else if (section_header->sh_type == SHT_NOTE)
		type = "SHT_NOTE";
	else if (section_header->sh_type == SHT_NOBITS)
		type = "SHT_NOBITS";
	else if (section_header->sh_type == SHT_REL)
		type = "SHT_REL";
	else if (section_header->sh_type == SHT_SHLIB)
		type = "SHT_SHLIB";
	else if (section_header->sh_type == SHT_DYNSYM)
		type = "SHT_DYNSYM";
	else if (section_header->sh_type == SHT_LOPROC)
		type = "SHT_LOPROC";
	else if (section_header->sh_type == SHT_HIPROC)
		type = "SHT_HIPROC";
	else if (section_header->sh_type == SHT_LOUSER)
		type = "SHT_LOUSER";
	else if (section_header->sh_type == SHT_HIUSER)
		type = "SHT_HIUSER";
	else if (section_header->sh_type == SHT_INIT_ARRAY)
		type = "SHT_INIT_ARRAY";
	else if (section_header->sh_type == SHT_FINI_ARRAY)
		type = "SHT_FINI_ARRAY";
	if (type != NULL)
		ft_printf("Type: %s\n", type);
	else
		ft_printf("Type: %u\n", section_header->sh_type);
}

char	*str_join(char **string_array, size_t array_size, char *separator)
{
	size_t	total_size;
	size_t	i;
	size_t	j;
	size_t	k;
	char	*str;

	if (array_size == 0)
	{
		str = ft_memalloc(1);
		if (str == NULL)
			return (NULL);
		return (str);
	}
	i = 0;
	total_size = 0;
	while (i < array_size)
	{
		total_size += ft_strlen(string_array[i]);
		i++;
	}
	if (array_size > 1)
		total_size += ft_strlen(separator) * (array_size - 1);
	str = malloc(total_size + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (i < array_size)
	{
		j = 0;
		while (string_array[i][j])
			str[k++] = string_array[i][j++];
		if (i != array_size - 1)
		{
			j = 0;
			while (separator[j])
				str[k++] = separator[j++];
		}
		i++;
	}
	str[total_size] = '\0';
	return (str);
}

void print_flags(Elf64_Shdr *section_header)
{
	t_vector flags;
	char *str;
	char *joined_flags;

	// TODO Check vector_add
	vector_init(&flags, sizeof(char *));
	if (section_header->sh_flags & SHF_WRITE)
	{
		str = "SHF_WRITE";
		vector_push(&flags, &str);
	}
	if (section_header->sh_flags & SHF_ALLOC)
	{
		str = "SHF_ALLOC";
		vector_push(&flags, &str);
	}
	if (section_header->sh_flags & SHF_EXECINSTR)
	{
		str = "SHF_EXECINSTR";
		vector_push(&flags, &str);
	}
	if (section_header->sh_flags & SHF_MASKPROC)
	{
		str = "SHF_MASKPROC";
		vector_push(&flags, &str);
	}
	joined_flags = str_join(flags.items, flags.total, " | ");
	ft_printf("Flags: %s\n", joined_flags);
	free(joined_flags);
	vector_free(&flags);
}

void print_section(Elf64_Shdr *section_header)
{
	print_type(section_header);
	print_flags(section_header);
}
